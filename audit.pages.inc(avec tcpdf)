function audit_my_form_submit($form, &$form_state) {
require(DRUPAL_ROOT.'/sites/all/libraries/PHPExcel/Classes/PHPExcel/IOFactory.php');
require(DRUPAL_ROOT.'/sites/all/libraries/PHPExcel/Classes/PHPExcel.php');
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
    $audit= &$form_state['audit'];
    $audit->ent_id = $entreprise->ent_id;
    audit_save($audit);
    dpm('avant exel');

//data to make csv (may be from database, form, etc)
    $dbdata = array();
    
    // Create new PHPExcel object
    $objPHPExcel = new PHPExcel(); 
    
    $rendererName = PHPExcel_Settings::PDF_RENDERER_TCPDF;
    
    // tcpdf folder
    $rendererLibraryPath = DRUPAL_ROOT.'/sites/all/libraries/tcpdf'; 

    
    //setting column heading
    $objPHPExcel->getActiveSheet(0)->setCellValue('A1',"Name"); 
    $objPHPExcel->getActiveSheet(0)->setCellValue('B1',"Phone"); 
    
    //setting column body
    $i=2; //starting from row 2 bcz row 1 set to header
    foreach($dbdata as $data) {
        $objPHPExcel->getActiveSheet(0)->setCellValue('A'.$i,$data['name']);
        $objPHPExcel->getActiveSheet(0)->setCellValue('B'.$i,$data['phone']);
        $i++;
    }
    
    // Rename sheet
    $objPHPExcel->getActiveSheet()->setTitle('Simple');

    // Set active sheet index to the first sheet, so Excel opens this as the first sheet
    $objPHPExcel->setActiveSheetIndex(0);
    
        
if (!PHPExcel_Settings::setPdfRenderer(
    $rendererName,
    $rendererLibraryPath
  )) {
  die(
    'NOTICE: Please set the $rendererName and $rendererLibraryPath values' .
    '<br />' .
    'at the top of this script as appropriate for your directory structure'
  );
}

// Redirect output to a client’s web browser (PDF)
header('Content-Type: application/pdf');
header('Content-Disposition: attachment;filename="01simple.pdf"');
header('Cache-Control: max-age=0');

$objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'PDF');
$objWriter->save('php://output');
exit;
