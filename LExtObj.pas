unit LExtObj ;

interface

{$IFDEF SYNTH_EXE}

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, DBTables, DB, DBCtrls, ExtCtrls, Grids,
  DbiProcs, DbiErrs, Math, DTypes, OleCtrls, ComObj,
  Menus, Buttons, DForm, Res, Menu, URdb, Bde0, Dsgn, Entity0, Prop, Lib0,
  DApp, BloxVisual_TLB, Blox_TLB, Blox ;

{================================ TExtObj =====================================}

type
    TExtObj = class ( TEntity0 )
    public
          generator : Integer ; // sets/gets the procedure that creates the Entity

          eidh_id   : Arguments ;  // for external objects
          pCount    : Integer ;   // properties count
          pval      : array [0..10] of String ;
          pname     : array [0..10] of String ;

          next_id,
          prior_id   : Integer ;
          carrier_id : Integer ;
          topoth     : Integer ;   // apo aristera = 0, apo dexia = 1

          yangle   : Double ;

          back_vec : array [0..2] of IVector ;

          left_top_point,
          right_top_point,
          left_base_point,
          right_base_point : IPosition ;   // in case of participation in a battery

          back_side        : Integer ;     // the back side syrface offset into the Syrfs[]

          procedure RecordToEntity ( p : TObject ) ; override ;
          procedure EntityToRecord ( p : TObject ) ; override ;

          procedure ReadProperties  ( id : Integer ; Text : String ) ; override ;
          procedure WriteProperties ( var prop_count : Integer ; var flag : Boolean ) ; override ;
          procedure PropBtnClick    ( prop : Integer ) ; override ;
          procedure AddPropItems    ( prop : Integer ) ; override ;

          // battery related routines
          procedure GetBattery ;
          procedure SetBatteryTopoth ( tpth : Integer ) ;
          function  GetBattOrder : Integer ;
          procedure Calculate_d1_d2    ( var d1, d2, slen : Double ) ;
          procedure Calculate_tx_ty_tz ( d1, d2 : Double ) ;
          procedure Delete ; override ;
          procedure Insert  ( new : TExtObj ; AddNewMode : Integer ) ;
          function  batt_width_total : Double ;

          function  Description : String ;

          procedure RotateBackSide ( side_id : Integer ; nvect : IVector ;
                                     mode : TransformCombinationConstants ) ;
          constructor Create ( Owner : TComponent ) ; override ;
          destructor  Destroy ; override ;
    end ;

// battery variables
var batt_pr    : array[0..100] of TExtObj ;
    batt_count : Integer ;

{$ENDIF}

implementation

{$IFDEF SYNTH_EXE}

uses LObject2, LObject3 ;

{================================ Create ================================}

constructor TExtObj.Create ( Owner : TComponent ) ;
var i : Integer ;
begin
     inherited ;

     left_top_point   := IPosition(CreateComObject(Class_Position)) ;
     right_top_point  := IPosition(CreateComObject(Class_Position)) ;
     left_base_point  := IPosition(CreateComObject(Class_Position)) ;
     right_base_point := IPosition(CreateComObject(Class_Position)) ;

     for i := 0 to 2 do
         back_vec[i] := IVector(CreateComObject(Class_Vector)) ;
end ;

{================================ Destroy ==============================}

destructor TExtObj.Destroy ;
var i : Integer ;
begin
     left_top_point   := nil ;
     right_top_point  := nil ;
     left_base_point  := nil ;
     right_base_point := nil ;

     for i := 0 to 2 do
         back_vec[i] := nil ;

     inherited ;
end ;

{========================= RecordToEntity ==========================}

procedure TExtObj.RecordToEntity ( p : TObject ) ;
var i : Integer ;
begin
     e.Attributes.AddNamed('Type','ExtObj') ;
     e.Attributes.AddNamed('Generator',generator) ;
     for i := 0 to NUM_ARGS do
         e.Attributes.AddNamed('Eidh_id'+Trim(IntToStr(i),' '),eidh_id[i]) ;

     e.Attributes.AddNamed('pCount',pCount) ;
     for i := 0 to pCount-1 do begin
         e.Attributes.AddNamed('pval'+Trim(IntToStr(i),' '),pval[i]) ;
         e.Attributes.AddNamed('pname'+Trim(IntToStr(i),' '),pname[i]) ;
     end ;

     e.Attributes.AddNamed('next_id',next_id) ;
     e.Attributes.AddNamed('prior_id',prior_id) ;
     e.Attributes.AddNamed('carrier_id',carrier_id) ;
     e.Attributes.AddNamed('topoth',topoth) ;
     e.Attributes.AddNamed('yangle',yangle) ;

     e.Attributes.AddNamed('left_top_pointx',left_top_point.x) ;
     e.Attributes.AddNamed('left_top_pointy',left_top_point.y) ;
     e.Attributes.AddNamed('left_top_pointz',left_top_point.z) ;

     e.Attributes.AddNamed('right_top_pointx',right_top_point.x) ;
     e.Attributes.AddNamed('right_top_pointy',right_top_point.y) ;
     e.Attributes.AddNamed('right_top_pointz',right_top_point.z) ;

     e.Attributes.AddNamed('left_base_pointx',left_base_point.x) ;
     e.Attributes.AddNamed('left_base_pointy',left_base_point.y) ;
     e.Attributes.AddNamed('left_base_pointz',left_base_point.z) ;

     e.Attributes.AddNamed('right_base_pointx',right_base_point.x) ;
     e.Attributes.AddNamed('right_base_pointy',right_base_point.y) ;
     e.Attributes.AddNamed('right_base_pointz',right_base_point.z) ;

     e.Attributes.AddNamed('back_side',back_side) ;

     inherited ;
end ;

{========================= EntityToRecord ==========================}

procedure TExtObj.EntityToRecord ( p : TObject ) ;
var count, i : Integer ;
begin
     generator := INamedAttribute(e.Attributes.Item('Generator').Entity.Object_).Value ;
     for i := 0 to NUM_ARGS do
         eidh_id[i] := INamedAttribute(e.Attributes.Item('Eidh_id'+Trim(IntToStr(i),' ')).Entity.Object_).Value ;

     pCount := INamedAttribute(e.Attributes.Item('pCount').Entity.Object_).Value ;
     for i := 0 to pCount-1 do begin
         pval[i]  := INamedAttribute(e.Attributes.Item('pval'+Trim(IntToStr(i),' ')).Entity.Object_).Value ;
         pname[i] := INamedAttribute(e.Attributes.Item('pname'+Trim(IntToStr(i),' ')).Entity.Object_).Value ;
     end ;

     next_id    := INamedAttribute(e.Attributes.Item('next_id').Entity.Object_).Value ;
     prior_id   := INamedAttribute(e.Attributes.Item('prior_id').Entity.Object_).Value ;
     carrier_id := INamedAttribute(e.Attributes.Item('carrier_id').Entity.Object_).Value ;
     topoth     := INamedAttribute(e.Attributes.Item('topoth').Entity.Object_).Value ;
     yangle     := INamedAttribute(e.Attributes.Item('yangle').Entity.Object_).Value ;

     left_top_point.x := INamedAttribute(e.Attributes.Item('left_top_pointx').Entity.Object_).Value ;
     left_top_point.y := INamedAttribute(e.Attributes.Item('left_top_pointy').Entity.Object_).Value ;
     left_top_point.z := INamedAttribute(e.Attributes.Item('left_top_pointz').Entity.Object_).Value ;

     right_top_point.x := INamedAttribute(e.Attributes.Item('right_top_pointx').Entity.Object_).Value ;
     right_top_point.y := INamedAttribute(e.Attributes.Item('right_top_pointy').Entity.Object_).Value ;
     right_top_point.z := INamedAttribute(e.Attributes.Item('right_top_pointz').Entity.Object_).Value ;

     left_base_point.x := INamedAttribute(e.Attributes.Item('left_base_pointx').Entity.Object_).Value ;
     left_base_point.y := INamedAttribute(e.Attributes.Item('left_base_pointy').Entity.Object_).Value ;
     left_base_point.z := INamedAttribute(e.Attributes.Item('left_base_pointz').Entity.Object_).Value ;

     right_base_point.x := INamedAttribute(e.Attributes.Item('right_base_pointx').Entity.Object_).Value ;
     right_base_point.y := INamedAttribute(e.Attributes.Item('right_base_pointy').Entity.Object_).Value ;
     right_base_point.z := INamedAttribute(e.Attributes.Item('right_base_pointz').Entity.Object_).Value ;

     back_side        := INamedAttribute(e.Attributes.Item('back_side').Entity.Object_).Value ;

     inherited ;
end ;

{========================= ReadProperties =========================}

procedure TExtObj.ReadProperties ( id : Integer ; Text : String ) ;
var i, show_id, topoth               : Integer ;
    len, angle, len1,
    d1, d2, slen, len2, ry   : Double ;
begin
     inherited ;

     if id <> -1 then exit ;

     for i := 0 to pCount-1 do
         if pval[i] <> TEdit(PEDIT.edit[i]).Text then
            pval[i] := TEdit(PEDIT.edit[i]).Text ;

     GetBattery ;
     batt_pr[0].Calculate_d1_d2 ( d1, d2, slen ) ;  // calculate slen

     d1 := StringToInteger0(TEdit(PEDIT.edit[pCount+1]).Text,0) ;
     d2 := StringToInteger0(TEdit(PEDIT.edit[pCount+2]).Text,0) ;

     ry := ry - yangle ;
     yangle := -StringToInteger0(TEdit(PEDIT.edit[pCount+0]).Text,0) ;
     ry := ry + yangle ;
     topoth := TComboBox(PEDIT.edit[pCount+4]).ItemIndex ;
     SetBatteryTopoth(topoth) ;

     len2 := batt_pr[0].batt_width_total ;

     len := 0 ;
     for i := 0 to batt_count-1 do begin
         if topoth = 0 then
            batt_pr[i].Calculate_tx_ty_tz ( d1+len, d2 )
         else
            batt_pr[i].Calculate_tx_ty_tz ( -d1+slen+len-len2, d2 ) ;
         len1 := APPL.BloxEng.MathObj.Distance(batt_pr[i].left_base_point,batt_pr[i].right_base_point) ;
         len := len + len1 ;
     end ;

     inherited ;
end ;

{============================ WriteProperties =====================}

procedure TExtObj.WriteProperties ( var prop_count : Integer ; var flag : Boolean ) ;
var i, topoth          : Integer ;
    len,
    len1, len2, len3,
    d1, d2, slen       : Double ;
begin
     inherited ;

     flag := True ;

     with PEDIT do begin
          prop_count := pCount ;
          for i := 0 to pCount-1 do begin
              lab[i] := pname[i] ;
              val[i] := pval[i] ;
              etype[i] := TEdit ;
          end ;

          // d1, d2, slen, angle
          GetBattery ;
          batt_pr[0].Calculate_d1_d2 ( d1, d2, slen ) ;

          len2 := batt_pr[0].batt_width_total ;

          // !!! overcommented code
          if topoth = 0 then        // αποσταση από αριαστερά
             d1 := d1
          else
             d1 := d1 + len2 - slen ;   // απόσταση από δεξιά

          lab[i+0] := 'Στροφή (μοιρες)' ;  val[i+0] := FloatToStr(Round(-yangle)) ;
          lab[i+1] := 'ΟΡΙΖΟΝΤΙΑ (mm)' ;   val[i+1] := FloatToStr(Round(abs(d1))) ;
          lab[i+2] := 'ΚΑΤΑΚΟΡΥΦΗ (mm)' ;  val[i+2] := FloatToStr(Round(d2)) ;
          lab[i+3] := 'ΟΛΙΚΟ ΜΗΚΟΣ' ;      val[i+3] := FloatToStr(Round(len2)) ;
          lab[i+4] := 'ΤΟΠΟΘΕΤΗΣΗ' ;       val[i+4] := IntToStr(topoth) ;

          etype[i+0] := TEdit ;
          etype[i+1] := TEdit ;
          etype[i+2] := TEdit ;
          etype[i+3] := TEdit ;
          etype[i+4] := TComboBox ;

          prop_count := i + 5 ;
     end ;
end ;

{============================= PropBtnClick =====================}

procedure TExtObj.PropBtnClick ( prop : Integer ) ;
begin
     inherited ;
end ;

{============================= AddPropItems =====================}

procedure TExtObj.AddPropItems ( prop : Integer ) ;
begin
     inherited ;
end ;

{============================= GetBattery ===============================}

procedure TExtObj.GetBattery ;
label out1 ;
var pr     : TExtObj ;
    cpo    : TEntity0 ;
    p      : TScene1 ;
    f      : TDForm ;
begin
     f := TDForm(Owner) ;
     p := f.GLPanel ;

     if (next_id = 0) and (prior_id = 0) then begin
        batt_count := 1 ;
        batt_pr[0] := self ;
        goto out1 ;
     end ;

     // goto start
     pr := self ;
     while pr.prior_id <> 0 do begin
           cpo := p.FindEntity(pr.prior_id) ;
           pr := TExtObj(cpo) ;
     end ;

     // get them all until next_id = 0
     batt_count := 0 ;
     while pr.next_id <> 0 do begin
           batt_pr[batt_count] := pr ;
           batt_count := batt_count+1 ;
           cpo := p.FindEntity(pr.next_id) ;
           pr  := TExtObj(cpo) ;
     end ;
     batt_pr[batt_count] := pr ;
     batt_count := batt_count+1 ;

out1 :
end ;

{============================== SetBatteryTopoth ====================}

procedure TExtObj.SetBatteryTopoth ( tpth : Integer ) ;
var i : Integer ;
begin
     for i := 0 to batt_count-1 do
         batt_pr[i].topoth := tpth ;
end ;

{============================== Delete ============================}

procedure TExtObj.Delete ;
var len, d1, d2, slen  : Double ;
    order, i           : Integer ;
begin
     inherited ;

     GetBattery ;
     order := GetBattOrder ;
     len   := APPL.BloxEng.MathObj.Distance(left_base_point,right_base_point) ;

     // ... is in the middle
     if (order+1 <= batt_count-1) and  (order-1 >= 0) then begin
        batt_pr[order+1].prior_id := prior_id ;
        batt_pr[order-1].next_id  := next_id ;
     end
     else
     // ... is the last
     if (order = batt_count-1) and (order-1 >= 0) then begin
        batt_pr[order-1].next_id := 0 ;
     end
     else
     // ... is the first
     if (order+1 <= batt_count-1) and  (order = 0) then begin
        batt_pr[order+1].prior_id := 0 ;
     end
     else
     // ... else is the only one  ( do nothing )
     begin
     end ;

     // move all to the left
     for i := order+1 to batt_count-1 do begin
         batt_pr[i].Calculate_d1_d2 ( d1, d2, slen ) ;
         batt_pr[i].Calculate_tx_ty_tz ( d1-len, d2 ) ;
     end ;

     batt_count := 0 ; // invalidate the battery

     e.Delete ;
     Free ;
end ;

{============================== Insert ============================}

procedure TExtObj.Insert ( new : TExtObj ; AddNewMode : Integer ) ;
var nglo               : TExtObj ;
    len, d1, d2, slen  : Double ;
    order, i           : Integer ;
begin
     nglo := new ;

     new.carrier_id  := carrier_id ;
     new.topoth := topoth ;

     GetBattery ;
     order := GetBattOrder ;
     len   := APPL.BloxEng.MathObj.Distance(new.left_base_point,new.right_base_point) ;

     if AddNewMode = 1 then begin  // απο αριστερά
        new.next_id  := id ;
        new.prior_id := prior_id ;
        prior_id     := nglo.id ;

        if order-1 >= 0 then begin
//           new.prior_id             := TExtObj(batt_pr[order-1].Parent).id ;
           batt_pr[order-1].next_id := nglo.id ;

           // move all to the left
           for i := order-1 downto 0 do begin
               batt_pr[i].Calculate_d1_d2 ( d1, d2, slen ) ;
               batt_pr[i].Calculate_tx_ty_tz ( d1-len, d2 ) ;
           end ;
        end ;
     end
     else
     if AddNewMode = 2 then begin  // από δεξιά
        new.prior_id := id ;
        new.next_id  := next_id ;
        next_id      := nglo.id ;

        if order+1 <= batt_count-1 then begin
//           new.next_id               := TExtObj(batt_pr[order+1].Parent).id ;
           batt_pr[order+1].prior_id := nglo.id ;

           // move all to the right
           for i := order+1 to batt_count-1 do begin
               batt_pr[i].Calculate_d1_d2 ( d1, d2, slen ) ;
               batt_pr[i].Calculate_tx_ty_tz ( d1+len, d2 ) ;
           end ;
        end ;
     end ;

     batt_count := 0 ; // invalidate the battery
end ;

{============================ GetBattOrder ==========================}

function TExtObj.GetBattOrder : Integer ;
var i : Integer ;
begin
     for i := 0 to batt_count-1 do
         if batt_pr[i] = self then begin
            Result := i ;
            break ;
         end ;
end ;


{================================== Calculate_d1_d2 ==========================}

procedure TExtObj.Calculate_d1_d2 ( var d1, d2, slen : Double ) ;
var cpo                  : TExtObj ;
//    cpo_syrf             : TGLPolygon ;
//    p                    : TGLPanel ;
    kor, x, y, z,
    xs, ys, zs,
    d, cosf              : Double ;
begin
{
     if cp_id = 0 then exit ;
     p   := TGLPanel(Parent) ;

     p.FindGLO(cp_id,TObject(cpo),TObject(cpo_syrf)) ;               // get room wall
     x := cpo_syrf.Point0(3).x ;
     y := cpo_syrf.Point0(3).y ;
     z := cpo_syrf.Point0(3).z ;
     xs := cpo_syrf.Side0(3).x ;
     ys := cpo_syrf.Side0(3).y ;
     zs := cpo_syrf.Side0(3).z ;
     slen := cpo_syrf.SideLen(3) ;

     // calculate d
     d    := sqrt(sqr(tx-x)+sqr(ty-y)+sqr(tz-z)) ; // (3)
     if Round(d) <> 0 then begin
        // calculate cosf
        cosf := ((tx-x)*xs+(ty-y)*ys+(tz-z)*zs)/slen/d ;   // (4)
        d1   := Round(d*cosf) ;     // (1)
        // calculate d1, d2
        d2   := Round(d*Cos(pi/2-ArcCos(cosf))) ; // (2)
     end
     else begin
        d1 := 0 ;
        d2 := 0 ;
     end ;
}
end ;

{=============================== Calculate_tx_ty_tz ===========================}

procedure TExtObj.Calculate_tx_ty_tz ( d1, d2 : Double ) ;
var glo, cpo             : TExtObj ;
//    cpo_syrf             : TGLPolygon ;
//    p                    : TGLPanel ;
    x, y, z,
    xs, ys, zs,
    slen, d, cosf,
    xb, yb, zb           : Double ;
    i                    : Integer ;
begin
{
     if cp_id = 0 then exit ;
     glo := self ;
     p   := TGLPanel(glo.Parent) ;

     p.FindGLO(cp_id,TObject(cpo),TObject(cpo_syrf)) ;      // get room wall
     x := cpo_syrf.Point0(3).x ;
     y := cpo_syrf.Point0(3).y ;
     z := cpo_syrf.Point0(3).z ;
     xs := cpo_syrf.Side0(3).x ;
     ys := cpo_syrf.Side0(3).y ;
     zs := cpo_syrf.Side0(3).z ;
     slen := cpo_syrf.SideLen(3) ;
 //    cpo.GetData(KGL_NORMAL,[@kor, @xb, @yb, @zb]) ;        // get cp base normal
 xb := 0 ; yb := -1 ; zb := 0 ;

     // d vect := d1 vect + d2 vect
     for i := 0 to glo.OmadCount-1 do begin
         glo.Omad[i].tx := x + (xs/slen)*d1 + (-xb)*d2 ;
         glo.Omad[i].ty := y + (ys/slen)*d1 + (-yb)*d2 ;
         glo.Omad[i].tz := z + (zs/slen)*d1 + (-zb)*d2 ;
     end ;
}
end ;

{================================ batt_width_total ===========================}

function TExtObj.batt_width_total : Double ;
var i : Integer ;
begin
     GetBattery ;

     // ολικό μήκος
     Result := 0 ;
     for i := 0 to batt_count-1 do
         Result := Result + APPL.BloxEng.MathObj.Distance(batt_pr[i].left_base_point,batt_pr[i].right_base_point) ;
end ;

{================================= Description ========================}

function TExtObj.Description : String ;
begin
     Result := 'xxxxxxxxxxxx' ;
//     Result := FloatToStr(kz[1]-kz[0])+' x '+FloatToStr(kx[2]+kx[3])+' x '+
//               FloatToStr(h)+' mm' ;
end ;

{================================ RotateBackSide ==================================}

procedure TExtObj.RotateBackSide ( side_id : Integer ; nvect : IVector ;
                                   mode : TransformCombinationConstants ) ;
var vec   : IVector ;
    pos   : IPosition ;
    angle : Double ;
begin
     vec := IVector(CreateComObject(Class_Vector)) ;
     pos := IPosition(CreateComObject(Class_Position)) ;

     if side_id = 0 then begin
        pos.Set_(0,0,0) ;
        vec.Set_(0,1,0) ;

        angle := ArcCos ( back_vec[side_id].x * nvect.x +
                          back_vec[side_id].y * nvect.y + back_vec[side_id].z * nvect.z ) ;
        APPL.BloxEng.TransObj.Rotation ( pos, vec, angle, mode ) ;
     end
     else
     if side_id = 1 then begin

     end ;

     vec := nil ;
     pos := nil ;
end ;

{$ENDIF}

end.