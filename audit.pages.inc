function audit_my_form_submit($form, &$form_state) {
require('/opt/ftp/aidopc_user/aidopc.fr/extranet/sites/all/libraries/fpdf181/fpdf.php');
  $audit = audit_new();
  $audit->is_new = empty($audit->aud_id);
  $form_state['audit'] = $audit;

  if(empty($form_state['values']['aud_id']) || $form_state['values']['aud_id'] == 0) {
    audit_save($audit);
    //****************************** ENTREPRISE *******************************
    $entreprise = entreprise_new();
    $entreprise->soc_title_verif = $form_state['values']['soc_title_verif'];
    $entreprise->soc_title_change = $form_state['values']['soc_title_change'];
    $entreprise->title = $form_state['values']['title'];
    $entreprise->is_new = empty($entreprise->ent_id);
    $form_state['entreprise'] = $entreprise;
    entreprise_save($entreprise);
    $audit = &$form_state['audit'];
    $audit->ent_id = $entreprise->ent_id;
    audit_save($audit);
    
    $pdf= new FPDF();
    $pdf->Addpage();
    $pdf->SetFont('Arial','B',18);
    $pdf->Cell('40','10','TESSSSSSSSST');
    $pdf->Output('I');
