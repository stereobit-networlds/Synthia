unit LObject2 ;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, DBTables, DB, DBCtrls, ExtCtrls, Grids,
  DbiProcs, DbiErrs, Lib0, GLib0, Math, DTypes,
  Menus, Buttons, DForm, Res, Menu, URdb, Bde0, GLPanel, GL, GLObj, GLObj1, GLObj0,
  Prop, Dsgn, DApp, Odig, Compile ;

type
    TObject2 = class ;

    TObject2 = class(TObject)
    public
          eidos       : Integer ;  // tetrapleyro, pentapleyro, exapleyro

          height0     : GLFloat ;
          pano_kal,
          kato_kal   : Integer ; // 1=υπάρχει πανω,κατω καλυψη, 0=οχι
          pleyres    : Integer ;
          len, angle : GLFloatBigArray ;
          toix       : array[0..8] of Integer ;  // 1=υπάρχει τοίχος, 0=οχι

          anal_count    : Integer ; // the number of sides that have been analysed
          anal_sides    : array[0..2] of Integer ; // ποιές πλευρές έχουν αναλυθει
          zcount        : array[0..2] of Integer ;    // πλήθος ζωνών
          zheight       : array[0..2,0..5] of GLFloat ;  // ύψη ζωνών
          zccount       : array[0..2,0..5] of Integer ;  // πλήθος στηλων ανά ζώνη
          zcwidth       : array[0..2,0..5,0..2] of GLFloat ;  // πλάτη στηλων
          zcobjcount    : array[0..2,0..5,0..2] of Integer ;  // πλήθος στοιχείων ανά στήλη
          objheight     : array[0..2,0..5,0..2,0..5] of GLFloat ;
          objdepth      : array[0..2,0..5,0..2,0..5] of GLFloat ;
          objtype       : array[0..2,0..5,0..2,0..5] of Integer ;

          curv_count    : Integer ; // the number of sides that have curvature
          curv_sides    : array[0..2] of Integer ; // ποιές είναι οι καμπύλες πλευρές
          curv_type     : array[0..2] of Integer ; // τύποι των καμπύλων πλευρών  (0=ευθέια)
          curv_angle    : array[0..2] of GLFloat ; // γωνίες των αντίστοιχων τόξων

          procedure FormToObject ;
          procedure ObjectToForm ;
          procedure TableToObject ( dt, mt : TDataSet ) ;

          procedure ProcToObject ( pr : TProcedure ) ;
          procedure ObjectToProc ( pr : TProcedure ) ;

          procedure GenerateObject ( p : TGLPanel ; id : GLuint ;
                                     eidh_id      : Arguments ;
                                     var show_id : Integer ; var glo0 : TObject ; rgen_flag : Boolean ) ;
    end ;

var obj2 : TObject2 ;  // this is the global instance of the TObject2

implementation

uses LLib, LGLObj, LGLObj0, LGLObj1, LGLObj2, LGLObj3 ;

{=================================== GenerateObject ================================}

procedure TObject2.GenerateObject ( p : TGLPanel ; id : GLuint ;
                                    eidh_id        : Arguments ;
                                    var show_id : Integer ; var glo0 : TObject ; rgen_flag : Boolean ) ;
var i, j, k, l, kk     : Integer ;
    ob                 : TGLObject ;
    op                 : TOrthoParall ;
    glo, glo00         : TGLO ;
    found              : Boolean ;
    x, y, z, x0, y0, z0,
    vx, vy, vz,
    sx, sy, sz,
    d1, d2, len1, tx, ty, tz  : GLFloat ;
    x01, y01, z01,
    x02, y02, z02,
    x00, y00, z00,
    zh, zcw, hh,
    x001, y001, z001           : GLFloat ;
    xx, yy, zz                 : GLFloatBigArray ;
    p1                         : TGLPoint0 ;
    pr                         : TProcedure ;
    et, mt                     : TSTable ;
    por_txt, syr_txt, val      : String ;
    typ                        : Integer ;
    k_red, k_green, k_blue,
    m_red, m_green, m_blue     : GLFloat ;
begin
     et := APPL.DBEng.work.TableByName('EIDH0') ;
     mt := APPL.DBEng.work.TableByName('_MREC') ;

     // load ANTIKEIMENO
     if not et.Seek ('EIDH0',[eidh_id[0]]) then exit ;
     if not mt.Seek ('_MREC',[et.d.FieldByName('_MREC').AsString]) then exit ;

     if mt.d.FieldByName('_MREC').AsInteger <> 1 then exit ; //// !!! for now
     
     TableToObject(et.d,mt.d) ;

     // load PORTAKI
     por_txt := '' ;
     if et.Seek ('EIDH0',[eidh_id[1]]) then
        if mt.Seek ('_MREC',[et.d.FieldByName('_MREC').AsString]) then begin
           pr := TProcedure.Create ;
           pr.Compile ;
           LoadVars_Table(pr,et.d,mt.d) ;
           pr.GetVariable( 'ΕΙΚΟΝΑ', por_txt, 0, typ ) ;
           por_txt := por_txt+'.bmp' ;
           pr.Free ;
        end ;

     // load SYRTARI
     syr_txt := '' ;
     if et.Seek ('EIDH0',[eidh_id[2]]) then
        if mt.Seek ('_MREC',[et.d.FieldByName('_MREC').AsString]) then begin
           pr := TProcedure.Create ;
           pr.Compile ;
           LoadVars_Table(pr,et.d,mt.d) ;
           pr.GetVariable( 'ΕΙΚΟΝΑ', syr_txt, 0, typ ) ;
           syr_txt := syr_txt+'.bmp' ;
           pr.Free ;
        end ;

     // load KASSOMA
     k_red := 1 ; k_green := 1 ; k_blue := 1 ;
     if et.Seek ('EIDH0',[eidh_id[3]]) then
        if mt.Seek ('_MREC',[et.d.FieldByName('_MREC').AsString]) then begin
           pr := TProcedure.Create ;
           pr.Compile ;
           LoadVars_Table(pr,et.d,mt.d) ;
           pr.GetVariable( 'ΚΟΚΚΙΝΟ', val, 0, typ ) ; k_red   := StringToInteger0(val,0)/255 ;
           pr.GetVariable( 'ΠΡΑΣΙΝΟ', val, 0, typ ) ; k_green := StringToInteger0(val,0)/255 ;
           pr.GetVariable( 'ΜΠΛΕ', val, 0, typ ) ;    k_blue  := StringToInteger0(val,0)/255 ;
           pr.Free ;
        end ;

     // load MPAZA
     m_red := 1 ; m_green := 1 ; m_blue := 1 ;
     if et.Seek ('EIDH0',[eidh_id[4]]) then
        if mt.Seek ('_MREC',[et.d.FieldByName('_MREC').AsString]) then begin
           pr := TProcedure.Create ;
           pr.Compile ;
           LoadVars_Table(pr,et.d,mt.d) ;
           pr.GetVariable( 'ΚΟΚΚΙΝΟ', val, 0, typ ) ; m_red   := StringToInteger0(val,0)/255 ;
           pr.GetVariable( 'ΠΡΑΣΙΝΟ', val, 0, typ ) ; m_green := StringToInteger0(val,0)/255 ;
           pr.GetVariable( 'ΜΠΛΕ', val, 0, typ ) ;    m_blue  := StringToInteger0(val,0)/255 ;
           pr.Free ;
        end ;

     p.GLS.Units := 1 ;  // mm

     // create the object
     if not Assigned(glo0) then begin
        glo00         := TGLO.Create(p) ;
        glo00.Kind    := KGL_BASE_TYPE ;
        for i := 0 to 10 do
            glo00.eidh_id[i] := eidh_id[i] ;
        glo00.id      := id ;

        // adjust user defined parameters
        if (eidos = 0) then begin   // aplo
           if (pleyres = 4) then begin
              glo00.pval[0]  := FloatToStr(len[3]) ;
              glo00.pname[0] := 'ΠΛΑΤΟΣ cm' ;
              glo00.pCount   := 1 ;
           end ;
        end
        else
        if (eidos = 1) then begin    // pentapleyro
           glo00.pval[0]  := FloatToStr(len[4]) ;
           glo00.pname[0] := 'ΠΛΑΤΟΣ ΑΡ. cm' ;
           glo00.pval[1]  := FloatToStr(len[3]) ;
           glo00.pname[1] := 'ΠΛΑΤΟΣ ΔΕ. cm' ;
           glo00.pval[2]  := FloatToStr(angle[4]) ;
           glo00.pname[2] := 'ΓΩΝΙΑ (μοιρ)' ;
           glo00.pCount   := 3 ;
        end
        else
        if (eidos = 2) then begin   // exapleyro
           glo00.pval[0]  := FloatToStr(len[5]) ;
           glo00.pname[0] := 'ΠΛΑΤΟΣ ΑΡ. cm' ;
           glo00.pval[1]  := FloatToStr(len[5]) ;
           glo00.pname[1] := 'ΠΛΑΤΟΣ ΔΕ. cm' ;
           glo00.pval[2]  := FloatToStr(angle[5]) ;
           glo00.pname[2] := 'ΓΩΝΙΑ (μοιρ)' ;
           glo00.pCount   := 3 ;
        end ;
     end
     else begin
        glo00 := TGLO(glo0) ;

        // adjust user defined parameters
        if (eidos = 0) then begin   // aplo
           if (pleyres = 4) then begin
              len[3] := StringToFloat0(glo00.pval[0],len[3]) ;
              len[1] := StringToFloat0(glo00.pval[0],len[3]) ;
           end ;
        end
        else
        if (eidos = 1) then begin    // pentapleyro

        end
        else
        if (eidos = 2) then begin   // exapleyro

        end ;
     end ;

     glo0  := glo00 ;
     glo00.GenerateFun := 'obj2' ;
     glo00.Symperifora := [syMetakinoymeno] ;
     ob := TGLObject(glo00.lobj) ;

     // define the polygon vertexes
     DefinePolygon000 ( pleyres, len, angle, 10, xx, yy, zz ) ;

     with ob do begin
          back_side := pleyres + 1 ;
          SyrfCount := pleyres + 2 ;

          // base
          if not Assigned(Syrfs[0]) then
             Syrfs[0] := TGLPolygon.Create(ob) ;
          Syrfs[0].PointCount := pleyres ;
          for i := 0 to pleyres-1 do
              p.DefinePoint0 ( Syrfs[0].Points[i], xx[i], yy[i], zz[i], True ) ;
          // set the curved sides
          TGLPolygon(Syrfs[0]).CurvCount := curv_count ;
          for i := 0 to curv_count-1 do begin
              TGLPolygon(Syrfs[0]).CurvSides[i]  := curv_sides[i]-1 ;
              TGLPolygon(Syrfs[0]).CurvAngles[i] := curv_angle[i] ;
              TGLPolygon(Syrfs[0]).CurvType[i]   := curv_type[i] ;
          end ;

          Syrfs[0].glo := glo0 ;
          Syrfs[0].id  := id ;
          if kato_kal = 0 then
             Syrfs[0].draw := True
          else
             Syrfs[0].draw := False ;
          Syrfs[0].reverse := True ;

          //top
          if not Assigned(Syrfs[1]) then
             Syrfs[1] := TGLPolygon.Create(ob) ;
          Syrfs[1].PointCount := Syrfs[0].PointCount ;
          for i := 0 to Syrfs[1].PointCount-1 do
              p.DefinePoint1(Syrfs[1].Points[i],Syrfs[0].Points[i],0,height0*10,0, True) ;
          // set the curved sides
          TGLPolygon(Syrfs[1]).CurvCount := curv_count ;
          for i := 0 to curv_count-1 do begin
              TGLPolygon(Syrfs[1]).CurvSides[i]  := curv_sides[i]-1 ;
              TGLPolygon(Syrfs[1]).CurvAngles[i] := curv_angle[i] ;
              TGLPolygon(Syrfs[1]).CurvType[i]   := curv_type[i] ;
          end ;
          Syrfs[1].glo := glo0 ;
          Syrfs[1].id  := id ;
          if pano_kal = 0 then
             Syrfs[1].draw := True
          else
             Syrfs[1].draw := False ;
          Syrfs[1].reverse := False ;

          for i := 2 to SyrfCount-1 do begin
              if not Assigned(Syrfs[i]) then
                 Syrfs[i] := TGLPolygon.Create(ob) ;
              Syrfs[i].PointCount := 4 ;

              Syrfs[i].Points[0] := Syrfs[0].Points[i-2] ;
              Syrfs[i].Points[1] := Syrfs[0].GetNextPoint(i-2) ;

              p.DefinePoint1(Syrfs[i].Points[2],Syrfs[i].Points[1],0,height0*10,0, True) ;
              p.DefinePoint1(Syrfs[i].Points[3],Syrfs[i].Points[0],0,height0*10,0, True) ;

              Syrfs[i].glo := glo0 ;
              Syrfs[i].id  := id ;
              Syrfs[i].reverse := False ;

              // οι επιφάνειες οι οποίες αναλύονται δεν σχεδιάζονται
              Syrfs[i].draw := True ;
              for j := 0 to anal_count-1 do
                  if anal_sides[j] = i-2+1 then begin
                     Syrfs[i].draw := False ;
                     break ;
                  end ;
          end ;

          // draw the shelves
          for l := 0 to anal_count-1 do begin
              zh := 0 ;
              for k := 0 to zcount[l]-2 do begin
                  zh := zh + zheight[l,k]*10 ;
                  j := SyrfCount ;
                  if not Assigned(Syrfs[j]) then
                     Syrfs[j] := TGLPolygon.Create(ob) ;
                  Syrfs[j].PointCount := Syrfs[0].PointCount ;
                  for i := 0 to Syrfs[j].PointCount-1 do
                      p.DefinePoint1(Syrfs[j].Points[i],Syrfs[0].Points[i],0,zh,0, True) ;
                  TGLPolygon(Syrfs[j]).CurvCount := curv_count ;
                  for i := 0 to curv_count-1 do begin
                      TGLPolygon(Syrfs[j]).CurvSides[i]  := curv_sides[i]-1 ;
                      TGLPolygon(Syrfs[j]).CurvAngles[i] := curv_angle[i] ;
                      TGLPolygon(Syrfs[j]).CurvType[i]   := curv_type[i] ;
                  end ;

                  Syrfs[j].glo := glo0 ;
                  Syrfs[j].id  := id ;
                  Syrfs[j].draw := True ; Syrfs[j].reverse := False ;
                  SyrfCount := SyrfCount + 1 ;
              end ;
          end ;

          // give color
          for i := 0 to SyrfCount-1 do begin
              Syrfs[i].r := k_red ;
              Syrfs[i].g := k_green ;
              Syrfs[i].b := k_blue ;
              Syrfs[i].doubleface := True ;
              Syrfs[i].CalculateRunTime ;
          end ;

          // battery variables
          left_base_point0  := Syrfs[0].Point0(0) ;
          right_base_point0 := Syrfs[0].Point0(pleyres-1) ;
          left_top_point0   := Syrfs[1].Point0(0) ;
          right_top_point0  := Syrfs[1].Point0(pleyres-1) ;

          // generate views ( if is the first and only object in the panel )
          if id = 100 then begin
             Syrfs[1].SetIntoView(1,p.GLS.GLVCount,'Κάτοψη') ;
             for i := 0 to pleyres-2 do begin
                 if i = anal_sides[0] then
                    show_id := i ;
                 Syrfs[i+2].SetIntoView(0,p.GLS.GLVCount,'Πλευρά '+inttostr(i+1)) ;
             end ;
          end ;

          // draw the second part of the object
          for i := 0 to anal_count-1 do begin
              x0   := xx[anal_sides[i]-1] ;
              y0   := yy[anal_sides[i]-1] ;
              z0   := zz[anal_sides[i]-1] ;
              x00  := xx[anal_sides[i]] ;
              y00  := yy[anal_sides[i]] ;
              z00  := zz[anal_sides[i]] ;
              p1   := p.GetPoint(Syrfs[1].Points[anal_sides[i]-1]).Point0 ;
              len1 := Syrfs[0].SideLen(anal_sides[i]-1) ;

              zh := 0 ;
              for j := 0 to zcount[i]-1 do begin
                  zcw := 0 ;
                  for k := 0 to zccount[i,j]-1 do begin
                      hh := 0 ;
                      for l := 0 to zcobjcount[i,j,k]-1 do begin
                          if objtype[i,j,k,l] <> 0 then begin  // <> empty
                             glo := TGLO.Create(p) ;
                             glo00.Omad[glo00.OmadCount] := glo ;
                             glo00.OmadCount := glo00.OmadCount + 1 ;
                             glo.Kind       := KGL_W1xW2xH ;
                             glo.parent_glo := glo00 ;
                             for kk := 0 to 10 do
                                 glo.eidh_id[kk] := eidh_id[kk] ;
                             glo.id      := id + l + 1 ;
                             glo.save    := False ;

                             // calculate start0 point
                             vx := (p1.x-x0)*(zh+hh)/(height0*10) ;
                             vy := (p1.y-y0)*(zh+hh)/(height0*10) ;
                             vz := (p1.z-z0)*(zh+hh)/(height0*10) ;
                             sx := (x00-x0)*zcw/len1 ;
                             sy := (y00-y0)*zcw/len1 ;
                             sz := (z00-z0)*zcw/len1 ;
                             glo.rx := 0 ; glo.ry := 0 ; glo.rz := 0 ;
                             op := TOrthoParall(glo.lobj) ;
                             op.w2 := objdepth[i,j,k,l]*10 ;
                             op.w1 := zcwidth[i,j,k]*10 ;
                             op.h  := objheight[i,j,k,l]*10 ;
                             op.start0.x := x0 + vx + sx ;
                             op.start0.y := y0 + vy + sy ;
                             op.start0.z := z0 + vz + sz ;
                             glo.Generate_flag := True ;
                             op.GenerateSyrfaces ;
                             // set the color
                             for kk := 0 to op.SyrfCount-1 do begin
                                 op.Syrfs[kk].r := k_red ;
                                 op.Syrfs[kk].g := k_green ;
                                 op.Syrfs[kk].b := k_blue ;
                             end ;
                             // treat each type of element
                             if objtype[i,j,k,l] in [2..5] then begin
                                op.Syrfs[3].Texture    := por_txt ;
                                op.Syrfs[3].TextWidth  := 0 ;
                                op.Syrfs[3].TextHeight := 0 ;
                             end ;
                             if objtype[i,j,k,l] in [1] then begin
                                op.Syrfs[3].Texture    := syr_txt ;
                                op.Syrfs[3].TextWidth  := 0 ;
                                op.Syrfs[3].TextHeight := 0 ;
                             end ;
                             if objtype[i,j,k,l] in [6] then begin
                                for kk := 0 to op.SyrfCount-1 do begin
                                    op.Syrfs[kk].r := m_red ;
                                    op.Syrfs[kk].g := m_green ;
                                    op.Syrfs[kk].b := m_blue ;
                                end ;
                             end ;
                          end ;
                          // objtype[i,j,k,l] ;
                          hh := hh + objheight[i,j,k,l]*10 ;
                      end ;
                      zcw := zcw + zcwidth[i,j,k]*10 ;
                  end ;
                  zh := zh + zheight[i,j]*10 ;
              end ;
          end ;
     end ; // with ob
end ;

{================================= FormToObject ==========================}

procedure TObject2.FormToObject ;
var f               : TDForm ;
    pr              : TProcedure ;
    mt              : TSTable ;
begin
     f := APPL.TopForm ;
     mt := f.DPanel[0].Data.TByName('_MREC') ;

     pr := TProcedure.Create ;
     pr.Compile ;
     LoadVars_Form(pr,f,mt.d) ;
     ProcToObject(pr) ;
     pr.Free ;
end ;

{================================= ObjectToForm ==========================}

procedure TObject2.ObjectToForm ;
var f               : TDForm ;
    pr              : TProcedure ;
    mt              : TSTable ;
begin
     f := APPL.TopForm ;
     mt := f.DPanel[0].Data.TByName('_MREC') ;

     pr := TProcedure.Create ;
     pr.Compile ;
     ObjectToProc(pr) ;
     SaveVars_Form(pr,f,mt.d) ;
     pr.Free ;
end ;

{================================ TableToObject ==============================}

procedure TObject2.TableToObject ( dt, mt : TDataSet ) ;
var pr : TProcedure ;
begin
     pr := TProcedure.Create ;
     pr.Compile ;
     LoadVars_Table ( pr, dt, mt ) ;
     ProcToObject(pr) ;
     pr.Free ;
end ;

{================================ ProcToObject =============================}

procedure TObject2.ProcToObject ( pr : TProcedure ) ;
var f               : TDForm ;
    typ             : Integer ;
    val, i_id       : String ;
    i, j, k, l, off : Integer ;
begin
     pr.GetVariable( 'ΕΙΔΟΣ', val, 0, typ ) ;   eidos    := StringToInteger0(val,0) ;
     pr.GetVariable( 'ΥΨΟΣ', val, 0, typ ) ;    height0  := StringToFloat0(val,0) ;
     pr.GetVariable( 'ΕΠΑΝΩ', val, 0, typ ) ;   pano_kal := StringToInteger0(val,0) ;
     pr.GetVariable( 'ΚΑΤΩ', val, 0, typ ) ;    kato_kal := StringToInteger0(val,0) ;
     pr.GetVariable( 'ΠΛΕΥΡΕΣ', val, 0, typ ) ; pleyres  := StringToInteger0(val,0) ;
     for i := 0 to 8 do begin
         i_id := LTrim(IntToStr((i+1))) ;
         pr.GetVariable( 'ΠΛ_ΜΗΚ'+i_id, val, 0, typ ) ;  len[i] := StringToFloat0(val,0) ;
         pr.GetVariable( 'ΠΛ_ΓΩΝ'+i_id, val, 0, typ ) ;  angle[i] := StringToFloat0(val,0) ;
         pr.GetVariable( 'ΠΛ_ΤΟΙΧ'+i_id, val, 0, typ ) ; toix[i] := StringToInteger0(val,0) ;
     end ;

     pr.GetVariable( 'ΠΛΗΘΟΣ_ΚΑΜΠ', val, 0, typ ) ;    curv_count := StringToInteger0(val,0) ;
     for i := 0 to 2 do begin
         i_id := LTrim(IntToStr((i+1))) ;
         pr.GetVariable( 'ΚΑΜΠ'+i_id, val, 0, typ ) ;       curv_sides[i] := StringToInteger0(val,0) ;
         pr.GetVariable( 'ΤΥΠΟΣ_ΚΑΜΠ'+i_id, val, 0, typ ) ; curv_type[i]  := StringToInteger0(val,0) ;
         pr.GetVariable( 'ΓΩΝΙΑ_ΚΑΜΠ'+i_id, val, 0, typ ) ; curv_angle[i] := StringToFloat0(val,0) ;
     end ;

     // read the second part of the object
     off := 1 ;
     i_id := LTrim(IntToStr((off))) ;
     pr.GetVariable('V'+i_id,val,0,typ) ; off := off + 1 ; anal_count := StringToInteger0(val,0) ;

     for i := 0 to anal_count-1 do begin
         i_id := LTrim(IntToStr((off))) ;
         pr.GetVariable('V'+i_id,val,0,typ) ; off := off + 1 ; anal_sides[i] := StringToInteger0(val,0) ;
     end ;
     for i := 0 to anal_count-1 do begin
         i_id := LTrim(IntToStr((off))) ;
         pr.GetVariable('V'+i_id,val,0,typ) ; off := off + 1 ; zcount[i] := StringToInteger0(val,0) ;
         for j := 0 to zcount[i]-1 do begin
             i_id := LTrim(IntToStr((off))) ;
             pr.GetVariable('V'+i_id,val,0,typ) ; off := off + 1 ; zheight[i,j] := StringToFloat0(val,0) ;
             i_id := LTrim(IntToStr((off))) ;
             pr.GetVariable('V'+i_id,val,0,typ) ; off := off + 1 ; zccount[i,j] := StringToInteger0(val,0) ;
             for k := 0 to zccount[i,j]-1 do begin
                 i_id := LTrim(IntToStr((off))) ;
                 pr.GetVariable('V'+i_id,val,0,typ) ; off := off + 1 ; zcwidth[i,j,k] := StringToFloat0(val,0) ;
                 i_id := LTrim(IntToStr((off))) ;
                 pr.GetVariable('V'+i_id,val,0,typ) ; off := off + 1 ; zcobjcount[i,j,k] := StringToInteger0(val,0) ;
                 for l := 0 to zcobjcount[i,j,k]-1 do begin
                     i_id := LTrim(IntToStr((off))) ;
                     pr.GetVariable('V'+i_id,val,0,typ) ; off := off + 1 ; objheight[i,j,k,l] := StringToFloat0(val,0) ;
                     i_id := LTrim(IntToStr((off))) ;
                     pr.GetVariable('V'+i_id,val,0,typ) ; off := off + 1 ; objdepth[i,j,k,l] := StringToFloat0(val,0) ;
                     i_id := LTrim(IntToStr((off))) ;
                     pr.GetVariable('V'+i_id,val,0,typ) ; off := off + 1 ; objtype[i,j,k,l] := StringToInteger0(val,0) ;
                 end ;
             end ;
         end ;
     end ;
end ;

{=============================== ObjectToProc =================================}

procedure TObject2.ObjectToProc ( pr : TProcedure ) ;
var typ             : Integer ;
    val, i_id       : String ;
    i, j, k, l, off : Integer ;
begin
     pr.SetVariable( 'ΕΙΔΟΣ', IntToStr(eidos), 0, typ ) ;
     pr.SetVariable( 'ΥΨΟΣ', FloatToStr(height0), 0, typ ) ;
     pr.SetVariable( 'ΕΠΑΝΩ', IntToStr(pano_kal), 0, typ ) ;
     pr.SetVariable( 'ΚΑΤΩ', IntToStr(kato_kal), 0, typ ) ;
     pr.SetVariable( 'ΠΛΕΥΡΕΣ', IntToStr(pleyres), 0, typ ) ;
     for i := 0 to 8 do begin
         i_id := LTrim(IntToStr((i+1))) ;
         pr.SetVariable( 'ΠΛ_ΜΗΚ'+i_id, FloatToStr(len[i]), 0, typ ) ;
         pr.SetVariable( 'ΠΛ_ΓΩΝ'+i_id, FloatToStr(angle[i]), 0, typ ) ;
         pr.SetVariable( 'ΠΛ_ΤΟΙΧ'+i_id, IntToStr(toix[i]), 0, typ ) ;
     end ;

     pr.SetVariable( 'ΠΛΗΘΟΣ_ΚΑΜΠ', IntToStr(curv_count), 0, typ ) ;
     for i := 0 to 2 do begin
         i_id := LTrim(IntToStr((i+1))) ;
         pr.SetVariable( 'ΚΑΜΠ'+i_id, IntToStr(curv_sides[i]), 0, typ ) ;
         pr.SetVariable( 'ΤΥΠΟΣ_ΚΑΜΠ'+i_id, IntToStr(curv_type[i]), 0, typ ) ;
         pr.SetVariable( 'ΓΩΝΙΑ_ΚΑΜΠ'+i_id, FloatToStr(curv_angle[i]), 0, typ ) ;
     end ;

     pr.SetVariable( 'ΔΗΜΙΟΥΡΓΙΑ', '', 0, typ ) ;
     pr.SetVariable( 'ΣΧΕΔΙΑΣΗ', '', 0, typ ) ;

     // save the second part of the object
     off := 1 ;
     i_id := LTrim(IntToStr((off))) ;
     pr.SetVariable('V'+i_id,IntToStr(anal_count),0,typ) ; off := off + 1 ;

     for i := 0 to anal_count-1 do begin
         i_id := LTrim(IntToStr((off))) ;
         pr.SetVariable('V'+i_id,IntToStr(anal_sides[i]),0,typ) ; off := off + 1 ;
     end ;
     for i := 0 to anal_count-1 do begin
         i_id := LTrim(IntToStr((off))) ;
         pr.SetVariable('V'+i_id,IntToStr(zcount[i]),0,typ) ; off := off + 1 ;
         for j := 0 to zcount[i]-1 do begin
             i_id := LTrim(IntToStr((off))) ;
             pr.SetVariable('V'+i_id,FloatToStr(zheight[i,j]),0,typ) ; off := off + 1 ;
             i_id := LTrim(IntToStr((off))) ;
             pr.SetVariable('V'+i_id,IntToStr(zccount[i,j]),0,typ) ; off := off + 1 ;
             for k := 0 to zccount[i,j]-1 do begin
                 i_id := LTrim(IntToStr((off))) ;
                 pr.SetVariable('V'+i_id,FloatToStr(zcwidth[i,j,k]),0,typ) ; off := off + 1 ;
                 i_id := LTrim(IntToStr((off))) ;
                 pr.SetVariable('V'+i_id,FloatToStr(zcobjcount[i,j,k]),0,typ) ; off := off + 1 ;
                 for l := 0 to zcobjcount[i,j,k]-1 do begin
                     i_id := LTrim(IntToStr((off))) ;
                     pr.SetVariable('V'+i_id,FloatToStr(objheight[i,j,k,l]),0,typ) ; off := off + 1 ;
                     i_id := LTrim(IntToStr((off))) ;
                     pr.SetVariable('V'+i_id,FloatToStr(objdepth[i,j,k,l]),0,typ) ; off := off + 1 ;
                     i_id := LTrim(IntToStr((off))) ;
                     pr.SetVariable('V'+i_id,IntToStr(objtype[i,j,k,l]),0,typ) ; off := off + 1 ;
                 end ;
             end ;
         end ;
     end ;
end ;

end.
