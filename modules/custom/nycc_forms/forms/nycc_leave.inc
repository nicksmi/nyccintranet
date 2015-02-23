<?php

function leave_calc_form($form, &$form_state) {
  
	// If the form has been submitted, output something related to the submission
	if ($form_state['submitted']) 
	{
		$form['submission'] = array(
		  '#markup' => leave_calc_results_output($form_state));
	}


	$format = 'd/m/Y';

	  $form['datecontinuousemp'] = array(
	     '#type' => 'date_popup', // types 'date_popup', 'date_text' and 'date_timezone' are also supported. See .inc file.
	     '#title' => t('The date you commenced continuous employment'),
	     '#date_format' => $format,
	     '#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
	     '#date_year_range' => '-50:+1',
	     '#required' => FALSE, 
	  );


	if (isset($form_state['storage']['datecontinuousemp'])) {
	  $form['datecontinuousemp']['#default_value'] = $form_state['storage']['datecontinuousemp'];
	}


	  $form['datenyccpoststart'] = array(
	     '#type' => 'date_popup', // types 'date_popup', 'date_text' and 'date_timezone' are also supported. See .inc file.
	     '#title' => t('Start date in NYCC post'),
	     '#date_format' => $format,
	     '#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
	     '#date_year_range' => '-50:+1',
	     '#required' => TRUE, 
	  );

	if (isset($form_state['storage']['datenyccpoststart'])) {
	  $form['datenyccpoststart']['#default_value'] = $form_state['storage']['datenyccpoststart'];
	}

	$d1 = strtotime('-6 years');
	$d2 = strtotime('+2 years');

	$years = range(date("Y", $d1), date("Y", $d2));
	$yearsOut = $years;

	foreach ($yearsOut as &$val)
	{
		$tempYear = $val+1;
		$val = $val ."/" . $tempYear;
	}


	$yearsOut = array_combine($years, $yearsOut);

	$form['leaveyear'] = array(
	   '#type' => 'select',
	   '#title' => t('Leave year'),
	   '#options' => $yearsOut,
	   '#default_value' => date("Y"),
	   '#required' => TRUE, 
	);

   	if (isset($form_state['storage']['leaveyear'])) {
	  $form['leaveyear']['#default_value'] = $form_state['storage']['leaveyear'];
	}


	  $form['dateofleaving'] = array(
	     '#type' => 'date_popup', // types 'date_popup', 'date_text' and 'date_timezone' are also supported. See .inc file.
	     '#title' => t('Your date of leaving the council'),
	     '#date_format' => $format,
	     '#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
	     '#required' => FALSE, 
	  );


	if (isset($form_state['storage']['dateofleaving'])) {
	  $form['dateofleaving']['#default_value'] = $form_state['storage']['dateofleaving'];
	}


	$form['hoursworked'] = array(
	    '#type' => 'textfield', 
	    '#title' => 'Hours worked',
	    '#size' => 4,
	    '#maxlength' => 4,
	    '#required' => TRUE, 
	    '#default_value' => 37,
  	);

	if (isset($form_state['storage']['hoursworked'])) {
	  $form['hoursworked']['#default_value'] = $form_state['storage']['hoursworked'];
	}

	$form['annualised'] = array(
	  '#type' =>
	'checkbox', 
	  '#title' => t('Annualised'),
	);

	if (isset($form_state['storage']['annualised'])) {
	  $form['annualised']['#default_value'] = $form_state['storage']['annualised'];
	}


	$form['totalweeks'] = array(
	    '#type' => 'textfield', 
	    '#title' => 'Total weeks',
	    '#size' => 2,
	    '#maxlength' => 2,
	    '#required' => TRUE, 
	    '#default_value' => 52,
  	);

	if (isset($form_state['storage']['totalweeks'])) {
	  $form['totalweeks']['#default_value'] = $form_state['storage']['totalweeks'];
	}


   $form['contracttype'] = array(
       '#type' => 'select',
       '#title' => t('Contract type'),
       '#options' => array(
          'NJC' => t('NJC'),
         'JNC' => t('JNC'),
         'Soulbury' => t('Soulbury'),
       ),
       '#default_value' => 'NJC',
       '#required' => TRUE, 
   );

   	if (isset($form_state['storage']['contracttype'])) {
	  $form['contracttype']['#default_value'] = $form_state['storage']['contracttype'];
	}


	$form['submit_button'] = array(
	'#type' => 'submit',
	'#value' => t('Get entitlement'),
  	);

  return $form;
}


function leave_calc_form_validate($form, &$form_state) {

	if($form_state['values']['annualised'] != 1)
	{

		if (($form_state['values']['hoursworked'] < 1) || ($form_state['values']['hoursworked'] > 37) ){
			form_set_error('hoursworked', t('Hours worked must be between 1 and 37'));
		}	
	}

	if (($form_state['values']['totalweeks'] < 1) || ($form_state['values']['totalweeks'] > 52) ){
		form_set_error('totalweeks', t('Total weeks must be between 1 and 52'));
	}
}


function leave_calc_form_submit($form, &$form_state) {
	

	$csDate = strtotime($form_state['values']['datecontinuousemp']);

	if(empty($form_state['values']['datecontinuousemp']))
	{
		$csDate = strtotime($form_state['values']['datenyccpoststart']);
	}

	$sDate = strtotime($form_state['values']['datenyccpoststart']);

	$eDate = strtotime($form_state['values']['dateofleaving']);

	if(empty($form_state['values']['dateofleaving']))
	{
		$eDate = strtotime('01/01/1800');
	}

	$sYear = $form_state['values']['leaveyear'];

	$hWorked = $form_state['values']['hoursworked'];

	$annHours = 'N';

	if($form_state['values']['annualised'] == 1)
	{
		$annHours = 'Y';
	}

	$cWeeks = $form_state['values']['totalweeks'];

	$cType = $form_state['values']['contracttype'];

	//Create the redundancy calc service ref
	$service = wsclient_service_load('leave_calculator');

	//Build the request for GetAgeAtLeaving
	$LeaveReq = array('parameters' => array('csDate' => date('d/m/Y', $csDate), 'sDate' => date('d/m/Y', $sDate), 'eDate' => date('d/m/Y', $eDate),
		'sYear' => $sYear, 'hWorked' => $hWorked, 'annHours' => $annHours, 'cWeeks' => $cWeeks, 'cType' => $cType));

	//Make the call
	$response = $service->invoke('CalcService', $LeaveReq);

	$form_state['result'] = $response->CalcServiceResult;

	if($form_state['values']['annualised'] != 1)
	{
		$form_state['result'] = "Your leave entitlement is <strong>" . $form_state['result'] . "</strong>";
	}
	else
	{
		$form_state['result'] = "<strong>" . $form_state['result'] . "</strong>";
	}
	
	$form_state['rebuild'] = TRUE;

}


function leave_calc_results_output(&$form_state) {

	$markup = "<h3 class='inline-result'><i class='fa fa-plane fa-3x'></i>{$form_state['result']}.</h3>";

	return $markup;
}