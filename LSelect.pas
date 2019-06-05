unit LSelect ;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, DBTables, DB, DBCtrls, ExtCtrls, Grids,
  DbiProcs, DbiErrs, Lib0, DTypes,
  Menus, Buttons, DForm, Res, Menu, URdb, Bde0, GLPanel, GL, GLObj, GLObj1, GLObj0,
  Prop, Dsgn, DApp, SelObj, Compile, Event ;

procedure SelectObj ;

type
    TSelect   = class ;

    TSelect = class(TObject)
    public
          omad_id, code_id, mrec_id,
          kas_id, port_id, syrt_id, xer_id, mpaz_id  : Longint ;
          ot, et, mt                                 : TSTable ;
          eid_id                                     : Arguments ;

          procedure WriteOdig0 ;
          procedure AddOdigItems0 ( prop : Integer ) ;

          procedure DefineLists ( Sender : TObject ) ;
          procedure DrawObject  ( Sender : TObject ) ;

          procedure Get_eidh_id ;
          procedure GoNext ;
          procedure GoPrev ;
          procedure FinishTask ( finish : Boolean ) ;
    end ;

implementation

uses LLib, LGLObj, LGLObj0, LGLObj1, LGLObj2, LGLObj3, LOdig2, LObject2, LObject3 ;

var Sel  : TSelect ;

{=============================== SelectObj ==============================}

procedure SelectObj ;
label out1 ;
begin
     if Assigned(SOEDIT.ff) then begin
        SOEDIT.ff.Visible := True ;
        goto out1 ;
     end ;

     Sel := TSelect.Create ;
     if not Assigned(obj2) then
        obj2  := TObject2.Create ;
     if not Assigned(obj3) then
        obj3  := TObject3.Create ;

     with Sel do begin

          with SOEDIT do begin
               capt := 'Επιλογή Αντικειμένου' ;

               WriteOdig    := WriteOdig0 ;
               AddOdigItems := AddOdigItems0 ;
               BtnOdigClick := nil ;
               SOEDIT.GoNext     := Sel.GoNext ;
               SOEDIT.GoPrev     := Sel.GoPrev ;
               SOEDIT.FinishTask := Sel.FinishTask ;

               OpenOdigEditor(fsStayOnTop) ;
          end ;
     end ;
out1 :
end ;

{=============================== TSelect ================================}

procedure TSelect.WriteOdig0 ;
begin
     with SOEDIT do begin
          prop_count := 7 ;                            // πορτες, συρταρια, χερουλια, μπαζα
          lab[0] := 'Μοντέλο' ; val[0] := IntToStr(omad_id) ;
          lab[1] := 'Υλικό' ;   val[1] := IntToStr(kas_id) ;
          lab[2] := 'Πορτάκι' ; val[2] := IntToStr(port_id) ;
          lab[3] := 'Συρτάρι' ; val[3] := IntToStr(syrt_id) ;
          lab[4] := 'Χερούλι' ; val[4] := IntToStr(xer_id) ;
          lab[5] := 'Μπάζα' ;   val[5] := IntToStr(mpaz_id) ;
          lab[6] := 'Αντικείμενο' ; val[6] := IntToStr(code_id) ;
          etype[0] := TComboBox ;
          etype[1] := TComboBox ;
          etype[2] := TComboBox ;
          etype[3] := TComboBox ;
          etype[4] := TComboBox ;
          etype[5] := TComboBox ;
          etype[6] := TComboBox ;
     end ;
end ;

procedure TSelect.AddOdigItems0 ( prop : Integer ) ;
begin
     with TComboBox(SOEDIT.edit[prop]).Items do begin
     Clear ;
     case prop of
     0    : begin
                 ot := APPL.DBEng.work.TableByName('OMAD') ;
                 ot.IndexName := 'OMAD_D' ;
                 ot.d.First ;
                 while not ot.d.EOF do begin
                       Add(ot.d.FieldByName('OMAD_D').AsString) ;
                       ot.d.Next ;
                 end ;

                 TComboBox(SOEDIT.edit[0]).OnChange := DefineLists ;
            end ;
     1    : TComboBox(SOEDIT.edit[1]).OnChange := DrawObject ;
     2    : TComboBox(SOEDIT.edit[2]).OnChange := DrawObject ;
     3    : TComboBox(SOEDIT.edit[3]).OnChange := DrawObject ;
     4    : TComboBox(SOEDIT.edit[4]).OnChange := DrawObject ;
     5    : TComboBox(SOEDIT.edit[5]).OnChange := DrawObject ;
     6    : TComboBox(SOEDIT.edit[6]).OnChange := DrawObject ;
     end ;
     end ;
end ;

procedure TSelect.DefineLists ( Sender : TObject ) ;
label out1 ;
var i : Integer ;
begin
     ot := APPL.DBEng.work.TableByName('OMAD') ;
     et := APPL.DBEng.work.TableByName('EIDH0') ;

     // clear off comboboxes
     for i := 1 to 6 do begin
         TComboBox(SOEDIT.edit[i]).OnChange := nil ;
         TComboBox(SOEDIT.edit[i]).Items.Clear ;
     end ;

     // ΑΝΤΙΚΕΙΜΕΝΟ
     if not ot.Seek('OMAD_D',[TComboBox(SOEDIT.edit[0]).Text]) then exit ;
     et.IndexName := 'EIDH0_C' ;
     et.d.First ;
     while not et.d.EOF do begin
           if (et.d.FieldByName('OMAD').AsString  = ot.d.FieldByName('OMAD').AsString) and
              ((et.d.FieldByName('_MREC').AsString = '1') or (et.d.FieldByName('_MREC').AsString = '7') ) then
              TComboBox(SOEDIT.edit[6]).Items.Add(et.d.FieldByName('EIDH0_C').AsString) ;
           et.d.Next ;
     end ;

     for i := 1 to 5 do begin
         SOEDIT.edit[i].Visible := False ;
         SOEDIT.lb[i].Visible := False ;
     end ;

     // αν το μοντελο περιεχει πάγκους τοτε ...

     if (ot.d.FieldByName('OMAD').AsString = '8') then begin


        // ... θα πρέπει να υπάρχει επιλεγμένο αντικείμενο κατάλλήλο να δεχτεί τον πάγκο
        if Assigned(MainGLP) then begin
           if Assigned(MainGLP.selected_glo) then begin
              if (TGLO(MainGLP.selected_glo).Kind <> KGL_BASE_TYPE) then begin
                 showmessage('Πρέπει να επιλεγεί το κατάλληλο αντικείμενο γιά την τοποθέτηση !') ;
                 goto out1 ;
              end ;
           end
           else begin
              showmessage('Πρέπει να επιλεγεί αντικείμενο γιά την τοποθέτηση !') ;
              goto out1 ;
           end ;
        end ;

     // YLIKO
     if not ot.Seek('OMAD_D',[TComboBox(SOEDIT.edit[0]).Text]) then exit ;

     SOEDIT.edit[1].Visible := True ;
     SOEDIT.lb[1].Visible  := True ;

     et.IndexName := 'EIDH0_D' ;
     et.d.First ;
     while not et.d.EOF do begin
           if (et.d.FieldByName('OMAD').AsString = ot.d.FieldByName('OMAD').AsString) and
              (et.d.FieldByName('_MREC').AsString = '9') then
              TComboBox(SOEDIT.edit[1]).Items.Add(et.d.FieldByName('EIDH0_D').AsString) ;
           et.d.Next ;
     end ;

     end  // ot = 7

     // αν το μοντελο περιεχει κύρια αντικείμενα (πρισματικά) τοτε ...

     else begin

     SOEDIT.edit[1].Visible := True ;
     SOEDIT.edit[2].Visible := True ;
     SOEDIT.edit[3].Visible := True ;
     SOEDIT.edit[4].Visible := True ;
     SOEDIT.edit[5].Visible := True ;
     SOEDIT.lb[1].Visible  := True ;
     SOEDIT.lb[2].Visible  := True ;
     SOEDIT.lb[3].Visible  := True ;
     SOEDIT.lb[4].Visible  := True ;
     SOEDIT.lb[5].Visible  := True ;

     // YLIKO
     if not ot.Seek('OMAD_D',[TComboBox(SOEDIT.edit[0]).Text]) then exit ;
     et.IndexName := 'EIDH0_D' ;
     et.d.First ;
     while not et.d.EOF do begin
           if (et.d.FieldByName('OMAD').AsString = ot.d.FieldByName('OMAD').AsString) and
              (et.d.FieldByName('_MREC').AsString = '3') then
              TComboBox(SOEDIT.edit[1]).Items.Add(et.d.FieldByName('EIDH0_D').AsString) ;
           et.d.Next ;
     end ;

     // ΠΟΡΤΑΚΙ
     if not ot.Seek('OMAD_D',[TComboBox(SOEDIT.edit[0]).Text]) then exit ;
     et.IndexName := 'EIDH0_D' ;
     et.d.First ;
     while not et.d.EOF do begin
           if (et.d.FieldByName('OMAD').AsString = ot.d.FieldByName('OMAD').AsString) and
              (et.d.FieldByName('_MREC').AsString = '2') then
              TComboBox(SOEDIT.edit[2]).Items.Add(et.d.FieldByName('EIDH0_D').AsString) ;
           et.d.Next ;
     end ;

     // ΣΥΡΤΑΡΙ
     if not ot.Seek('OMAD_D',[TComboBox(SOEDIT.edit[0]).Text]) then exit ;
     et.IndexName := 'EIDH0_D' ;
     et.d.First ;
     while not et.d.EOF do begin
           if (et.d.FieldByName('OMAD').AsString = ot.d.FieldByName('OMAD').AsString) and
              (et.d.FieldByName('_MREC').AsString = '4') then
              TComboBox(SOEDIT.edit[3]).Items.Add(et.d.FieldByName('EIDH0_D').AsString) ;
           et.d.Next ;
     end ;

     // ΧΕΡΟΥΛΙ
     if not ot.Seek('OMAD_D',[TComboBox(SOEDIT.edit[0]).Text]) then exit ;
     et.IndexName := 'EIDH0_D' ;
     et.d.First ;
     while not et.d.EOF do begin
           if (et.d.FieldByName('OMAD').AsString = ot.d.FieldByName('OMAD').AsString) and
              (et.d.FieldByName('_MREC').AsString = '5') then
              TComboBox(SOEDIT.edit[4]).Items.Add(et.d.FieldByName('EIDH0_D').AsString) ;
           et.d.Next ;
     end ;

     // ΜΠΑΖΑ
     if not ot.Seek('OMAD_D',[TComboBox(SOEDIT.edit[0]).Text]) then exit ;
     et.IndexName := 'EIDH0_D' ;
     et.d.First ;
     while not et.d.EOF do begin
           if (et.d.FieldByName('OMAD').AsString = ot.d.FieldByName('OMAD').AsString) and
              (et.d.FieldByName('_MREC').AsString = '6') then
              TComboBox(SOEDIT.edit[5]).Items.Add(et.d.FieldByName('EIDH0_D').AsString) ;
           et.d.Next ;
     end ;

     end ;  // if ot ...

     for i := 1 to 6 do
         TComboBox(SOEDIT.edit[i]).OnChange := DrawObject ;
out1 :
end ;

procedure TSelect.Get_eidh_id ;
var eid_c, mod_id : String ;
    i             : Integer ;
begin
     et := APPL.DBEng.work.TableByName('EIDH0') ;
     mt := APPL.DBEng.work.TableByName('_MREC') ;
     ot := APPL.DBEng.work.TableByName('OMAD') ;

     for i := 0 to 10 do eid_id[i] := '' ;

     // load MONDELO
     if not ot.Seek ('OMAD_D',[TComboBox(SOEDIT.edit[0]).Text]) then exit ;
     mod_id := ot.d.FieldByName('OMAD').AsString ;

     // load ANTIKEIMENO
     eid_c  := TComboBox(SOEDIT.edit[6]).Text ;
     if eid_c = '' then exit ;
     if not et.Seek ('OEIDH0_C',[mod_id,eid_c]) then exit ;
     eid_id[0] := et.d.FieldByName('EIDH0').AsString ;
     mrec_id   := et.d.FieldByName('_MREC').AsInteger ;

     // load PORTAKIA
     if et.Seek ('OEIDH0_D',[mod_id,TComboBox(SOEDIT.edit[2]).Text]) then
        eid_id[1] := et.d.FieldByName('EIDH0').AsString ;

     // load SYRTARIA
     if et.Seek ('OEIDH0_D',[mod_id,TComboBox(SOEDIT.edit[3]).Text]) then
        eid_id[2] := et.d.FieldByName('EIDH0').AsString ;

     // load KASSOMA
     if et.Seek ('OEIDH0_D',[mod_id,TComboBox(SOEDIT.edit[1]).Text]) then
        eid_id[3] := et.d.FieldByName('EIDH0').AsString ;

     // load MPAZA
     if et.Seek ('OEIDH0_D',[mod_id,TComboBox(SOEDIT.edit[5]).Text]) then
        eid_id[4] := et.d.FieldByName('EIDH0').AsString ;
end ;

procedure TSelect.DrawObject ( Sender : TObject ) ;
var show_id : Integer ;
    glo0    : TObject ;
begin
     Get_eidh_id ;

     SOEDIT.g.Setup ;
     SOEDIT.g.DrawQuality := SOEDIT.DrawQuality ;
     if SOEDIT.g.DrawQuality = dqFrames then     //// !!!!! fix
        SOEDIT.g.DrawQuality := dqFramesSyrfs ;
     
     glo0 := nil ;
     if mrec_id = 1 then
        obj2.GenerateObject ( SOEDIT.g, 100, eid_id, show_id, glo0, False )
     else
     if mrec_id = 7 then begin
        obj3.base_eid_id := '' ;
        if Assigned(MainGLP) then
           obj3.base_eid_id := TGLO(MainGLP.selected_glo).eidh_id[0] ;
        obj3.GenerateObject ( SOEDIT.g, 100, eid_id, show_id, glo0, False ) ;
     end ;

     SOEDIT.g.GLS.SetupView(SOEDIT.g,show_id) ;
     InvalidateRect(SOEDIT.g.Handle,nil,False);
end ;

{================================== GoNext ================================}

procedure TSelect.GoNext ;
begin
     if TComboBox(SOEDIT.edit[6]).ItemIndex < TComboBox(SOEDIT.edit[6]).Items.Count-1 then begin
        TComboBox(SOEDIT.edit[6]).ItemIndex := TComboBox(SOEDIT.edit[6]).ItemIndex + 1 ;
        DrawObject(nil) ;
     end ;
end ;

{================================== GoPrev ================================}

procedure TSelect.GoPrev ;
begin
     if TComboBox(SOEDIT.edit[6]).ItemIndex > 0 then begin
        TComboBox(SOEDIT.edit[6]).ItemIndex := TComboBox(SOEDIT.edit[6]).ItemIndex - 1 ;
        DrawObject(nil) ;
     end ;
end ;

{=================================== FinishTask ================================}

procedure TSelect.FinishTask ( finish : Boolean ) ;
label out1 ;
var f1   : TDForm ;
    glp  : TGLPanel ;
begin
     if not finish then goto out1 ;

     f1 := TDForm(APPL.GLForm) ;
     if not Assigned(f1) then goto out1 ;

     if (MainGLP.AddNewMode = anmFree) and
        (MainGLP.apply_glo[0] <> nil) then begin
        if (syStatheroOriz in TGLO(MainGLP.apply_glo[0]).Symperifora) or
           (syStatheroKat in TGLO(MainGLP.apply_glo[0]).Symperifora) then begin
           glp := f1.GLPanel ;
           Get_eidh_id ;

           if mrec_id = 1 then
              glp.GenerateObject := obj2.GenerateObject
           else
           if mrec_id = 7 then
              glp.GenerateObject := obj3.GenerateObject ;

           glp.AddFromPalette(SOEDIT.g,eid_id) ;
           SetProcess('PRC_ADD_TGLO') ;
        end ;
     end
     else
     if (MainGLP.AddNewMode in [anmLeft,anmRight]) and
        (MainGLP.selected_glo <> nil) then begin
        if (syMetakinoymeno in TGLO(MainGLP.selected_glo).Symperifora) then begin
           glp := f1.GLPanel ;
           Get_eidh_id ;

           if mrec_id = 1 then
              glp.GenerateObject := obj2.GenerateObject
           else
           if mrec_id = 7 then
              glp.GenerateObject := obj3.GenerateObject ;

           glp.AddFromPalette(SOEDIT.g,eid_id) ;
           SetProcess('PRC_ADD_TGLO') ;
        end ;
     end ;

out1 :
     SOEDIT.ff.Visible := False ;
end ;

end.
