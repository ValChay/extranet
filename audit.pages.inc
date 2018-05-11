function audit_my_form_submit($form, &$form_state) {
require('sites/all/libraries/fpdf181/fpdf.php');
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

    dpm("avant audit_download");
    $form_state['redirect'] = 'pdf';

    $url = NULL;
    audit_download($url, $form);
    dpm("après redirect");

function audit_contents() {
            return l(t('Download pdf'), 'pdf/download/pdf_form');
      } 
      function audit_download($url=null,$form) {
        $form =array();
        switch ($url) {
          case 'pdf_form':
            $pdf = audit_simple_pdf($form);
            dpm("dans le switch");
            dpm("valeur$form");
            break;
          default:
            return t('No such example.');
        }
        if (!$pdf) {
          return t('An error occured.');
        }
        dpm("dans audit download avant le header");
        header('Content-Type: application/pdf');
        header('Content-Length: ' . strlen($pdf));
        header('Content-Disposition: attachment; filename="pdf_form.pdf"');
        print $pdf;
        // Tell the browser that this is not an HTML file to show, but a pdf file to
        // download.
        
        return NULL;
      }
      function audit_simple_pdf($form) {
        // Get the content we want to convert into pdf.
        $form = array();
        dpm("Audit_simpple pdf");
        dpm($form);
        $html = theme('audit_basic_html');
        dpm($html);
        // Never make an instance of TCPDF or TCPDFDrupal classes manually.
        // Use tcpdf_get_instance() instead.
        $tcpdf = tcpdf_get_instance($form);
        /* DrupalInitialize() is an extra method added to TCPDFDrupal that initializes
        *  some TCPDF variables (like font types), and makes possible to change the
        *  default header or footer without creating a new class.
        */
        $tcpdf->DrupalInitialize(array(
          'footer' => array(
            'html' => 'This is a test!! <em>Bottom of the page</em>'
          ),
          'header' => array(
            'callback' => array(
              'function' => 'audit_default_header',
              // You can pass extra data to your callback.
              'context' => array(
                'welcome_message' => 'Hello, context array!',
              ),
            ),
          ),
        ));

        // Insert the content. Note that DrupalInitialize automaticly adds the first
        // page to the pdf document.
        $tcpdf->writeHTML($html);
        //dpm($tcpdf);

        return $tcpdf->Output('', 'S');
        
      }

      function audit_default_header(&$tcpdf, $context) {
        // $args contains passed variable...
        $theme_settings = variable_get('theme_' . variable_get('theme_default', '') . '_settings', '');
        if (isset($theme_settings['logo_path']) && (file_exists($theme_settings['logo_path']))) {
          $tcpdf->Image(drupal_realpath($theme_settings['logo_path']), 10, 10, 30, 0, '', variable_get('site_url', ''), '', TRUE, 150, '', FALSE, FALSE, 0, FALSE, FALSE, FALSE);
        }
        $tcpdf->Write(0, $context['welcome_message'], '', 0, 'J', true, 0, false, true, 0);
      }
  
