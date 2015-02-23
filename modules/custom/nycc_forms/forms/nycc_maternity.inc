<?php

function maternity_calc_form($form, &$form_state) {
  
   // If the form has been submitted, output something related to the submission
  if ($form_state['submitted'] && $form_state['values']['submit_button'] != 'Re-calculate') 
  {
    $form['submission'] = array(
      '#markup' => maternity_calc_results_output($form_state));

	$form['#attributes'] = array('class' => array('form-results'));


	$form['submit_button'] = array(
	'#type' => 'submit',
	'#value' => t('Re-calculate'),
  	);

  }
  else {

		$format = 'd/m/Y';

		  $form['startdate'] = array(
		     '#type' => 'date_popup', // types 'date_popup', 'date_text' and 'date_timezone' are also supported. See .inc file.
		     '#title' => t('Start date with NYCC (dd/mm/yyyy)'),
		     '#date_format' => $format,
		     '#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
		     '#date_year_range' => '-50:+1',
		     '#required' => TRUE, 
		  );

		if (isset($form_state['storage']['startdate'])) {
		  $form['startdate']['#default_value'] = $form_state['storage']['startdate'];
		}


		  $form['datecontinuousemp'] = array(
		     '#type' => 'date_popup', // types 'date_popup', 'date_text' and 'date_timezone' are also supported. See .inc file.
		     '#title' => t('Start date of continuous service (dd/mm/yyyy)'),
		     '#date_format' => $format,
		     '#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
		     '#date_year_range' => '-50:+1',
		     '#required' => TRUE, 
		  );


		if (isset($form_state['storage']['datecontinuousemp'])) {
		  $form['datecontinuousemp']['#default_value'] = $form_state['storage']['datecontinuousemp'];
		}

		

		  $form['expecteddate'] = array(
		     '#type' => 'date_popup', // types 'date_popup', 'date_text' and 'date_timezone' are also supported. See .inc file.
		     '#title' => t('Expected date of childbirth (dd/mm/yyyy)'),
		     '#date_format' => $format,
		     '#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
		     '#required' => TRUE, 
		  );


		if (isset($form_state['storage']['expecteddate'])) {
		  $form['expecteddate']['#default_value'] = $form_state['storage']['expecteddate'];
		}


	   $form['niflag'] = array(
	       '#type' => 'select',
	       '#title' => t('Do you pay national insurance contribution on a regular basis?'),
	       '#options' => array(
	          'Yes' => t('Yes'),
	         'No' => t('No'),
	       ),
	       '#default_value' => 'Yes',
	       '#required' => TRUE, 
	   );

	   	if (isset($form_state['storage']['niflag'])) {
		  $form['niflag']['#default_value'] = $form_state['storage']['niflag'];
		}

	   $form['contracttype'] = array(
	       '#type' => 'select',
	       '#title' => t('Are you employed on a contractual or irregular relief/casual basis?'),
	       '#options' => array(
	          'Contractual' => t('Contractual'),
	         'Relief/casual' => t('Relief/casual'),
	       ),
	       '#default_value' => 'Contractual',
	       '#required' => TRUE, 
	   );

	   	if (isset($form_state['storage']['contracttype'])) {
		  $form['contracttype']['#default_value'] = $form_state['storage']['contracttype'];
		}


	   $form['teacher'] = array(
	       '#type' => 'select',
	       '#title' => t('Are you a teacher employed under the School Teachers Pay and Conditions document?'),
	       '#options' => array(
	          'Yes' => t('Yes'),
	         'No' => t('No'),
	       ),
	       '#default_value' => 'No',
	       '#required' => TRUE, 
	   );

	   	if (isset($form_state['storage']['teacher'])) {
		  $form['teacher']['#default_value'] = $form_state['storage']['teacher'];
		}

	   $form['returntowork'] = array(
	       '#type' => 'select',
	       '#title' => t('Do you intend to return to work?'),
	       '#options' => array(
	          'Yes' => t('Yes'),
	         'No' => t('No'),
	         'Unsure' => t('Unsure'),
	       ),
	       '#default_value' => 'Yes',
	       '#required' => TRUE, 
	   );

	   	if (isset($form_state['storage']['returntowork'])) {
		  $form['returntowork']['#default_value'] = $form_state['storage']['returntowork'];
		}


		$form['submit_button'] = array(
		'#type' => 'submit',
		'#value' => t('Get maternity entitlement'),
	  	);
	}

  return $form;
}


function maternity_calc_form_validate($form, &$form_state) {


}


function maternity_calc_form_submit($form, &$form_state) {
	
	if ($form_state['values']['submit_button'] != 'Re-calculate') 
	{

		$sDate = strtotime($form_state['values']['startdate']);

		$cDate = strtotime($form_state['values']['datecontinuousemp']);

		$eDate = strtotime($form_state['values']['expecteddate']);

		$niFlag = $form_state['values']['niflag'];

		$conType = $form_state['values']['contracttype'];

		$teacher = $form_state['values']['teacher'];

		$returnToWork = $form_state['values']['returntowork'];

		//Create the redundancy calc service ref
		$service = wsclient_service_load('maternity_calculator');

		//Build the request for GetAgeAtLeaving
		$MaternityReq = array('parameters' => array('sDate' => date('d/m/Y', $sDate), 'cDate' => date('d/m/Y', $cDate), 'eDate' => date('d/m/Y', $eDate),
			'niFlag' => $niFlag, 'conType' => $conType, 'teacher' => $teacher, 'returnToWork' => $returnToWork));

		//Make the call
		$response = $service->invoke('CalculateMatLeave', $MaternityReq);

		$form_state['result'] = $response->CalculateMatLeaveResult->string;


		$form_state['storage']['startdate'] = $form_state['values']['startdate'];
		$form_state['storage']['datecontinuousemp'] = $form_state['values']['datecontinuousemp'];
		$form_state['storage']['expecteddate'] = $form_state['values']['expecteddate'];
		$form_state['storage']['niflag'] = $form_state['values']['niflag'];
		$form_state['storage']['contracttype'] = $form_state['values']['contracttype'];
		$form_state['storage']['teacher'] = $form_state['values']['teacher'];
		$form_state['storage']['returntowork'] = $form_state['values']['returntowork'];

	}

	$form_state['rebuild'] = TRUE;
}


function maternity_calc_results_output(&$form_state) {

	$markup = "";

	if($form_state['result'][0] == "Based on the information provided your entitlements are:")
	{
		$markup = "
	     		<h3>Maternity Leave entitlement</h3> 
	     		<p>You are entitled to 26 weeks ordinary maternity leave OML
	    		and 26 weeks additional maternity leave AML 52 weeks in  total.</p>";


         if($form_state['result'][1] == "2.1")
         {
         	$markup = $markup. "
	              <p>You are not entitled to statutory maternity pay. However you may be entitled to a maternity allowance, you 
	              will be provided with a form and guidance from Financial Services when you have provided your MATB1 to your manager.</p>";
         }   	

         if($form_state['result'][1] == "2.2")
         {
         	$markup = $markup. "
	                 <h3>Statutory maternity pay entitlement</h3>
	                 <p>You are not entitled to statutory maternity pay. However you may be entitled to a maternity allowance, you
	                 will be provided with a form and guidance from Financial Services when you have provided your MATB1 to your manager.</p>";
         }  

         if($form_state['result'][1] == "2.4")
         {
         	$markup = $markup. "
	                 <h3>Statutory maternity pay entitlement</h3>
	                 <p>You may be entitled to statutory maternity pay for 39 weeks. For the first 6 weeks this will be paid at 90% of your average
	                 week's pay and for the following weeks at the standard rate of statutory maternity pay. This will however be off set
	                 against any occupational maternity payment should you be entitled.</p>";
         } 

         if($form_state['result'][1] == "2.5")
         {
         	$markup = $markup. "
	                 <h3>Statutory maternity pay entitlement</h3>
	                 <p>You may not be entitled to statutory maternity pay. If you are not entitled you will be provided with a form and guidance
	                 Financial Services when you have provided your MATB1 to your manager.</p>";
         } 


         if($form_state['result'][2] == "1")
         {
         	$markup = $markup. "
	                 <h3>Occupational maternity pay entitlement</h3>
	                 <p>You are not entitled to occupational maternity pay as you are not contractually entitled to it.</p>";
         } 

         if($form_state['result'][2] == "2")
         {
         	$markup = $markup. "
	                <h3>Occupational maternity pay entitlement</h3>
	                 <p>You are not entitled to occupational maternity pay because you do not have enough continuous service.</p>";
         } 

         if($form_state['result'][2] == "3.1")
         {
         	$markup = $markup. "
	             <h3>Occupational maternity pay entitlement</h3>
	             <p>As you have stated it is your intention to return to work following your maternity leave you are entitled to: <br />
	             <strong>Weeks 1 - 6 90% of average earnings</strong> (offset against any statutory maternity pay or maternity allowance payments if applicable) <br />
	             <strong>Weeks 7 - 18 half pay</strong> (plus statutory maternity pay or maternity allowance, to a limit of full pay if applicable) <br />
	             (Weeks 19 - 39 statutory maternity pay or maternity allowance payments if applicable) <br />
	             <br />
	             Please note that half pay entitlements are only paid to those that return to employment.</p>";
         } 

         if($form_state['result'][2] == "3.2")
         {
         	$markup = $markup. "
	                <h3>Occupational maternity pay entitlement</h3>
	                <p>As you have stated it is not your intention to return to work following your maternity leave you are entitled to: <br />
	                <strong>Weeks 1 - 6 90% of average earnings</strong> (offset against any statutory maternity pay or maternity allowance payments if applicable) <br />
	                (Weeks 7 - 39  statutory maternity pay or maternity allowance if applicable)</p>";
         } 

         if($form_state['result'][2] == "3.3")
         {
         	$markup = $markup. "
	                <p><h3>Occupational maternity pay entitlement</h3>
	                <p>As you have stated you are unsure about returning to work following your maternity leave you have the following options: <br />
	                <strong>1.</strong>If you return to work you are entitled to: <br />
	                <strong>Weeks 1 - 6 90% of average earnings</strong> (offset against any statutory maternity pay or maternity allowance payments if applicable) <br />
	                <strong>Weeks 7 - 18 half pay </strong>(plus statutory maternity pay or maternity allowance, to a limit of full pay if applicable) <br />
	                (Weeks 19 - 39 statutory maternity pay or maternity allowance payments if applicable)             
	                <strong>2.</strong>If you do not return to work you are entitled to: <br />
	                <strong>Weeks 1 - 6 90% of average earnings</strong> (offset against any statutory maternity pay or maternity allowance payments if applicable) <br />
	                (Weeks 7 - 39 statutory maternity pay or maternity allowance payments if applicable) <br /> 
	                <br />
	                Please note that half pay entitlements are only paid to those that return to employment. If you remain undecided you can elect to have your 
	                half pay entitlement withheld until your decision has been made.</p>";
         } 


         if($form_state['result'][2] == "4.1")
         {
         	$markup = $markup. "
	                <h3>Occupational maternity pay entitlement</h3>
	                <p>As you have stated it is your intention to return to work following your maternity leave you are entitled to: <br />
	                <strong>Weeks 1 - 4 full pay</strong> (offset against any statutory maternity pay or maternity allowance payments if applicable) <br />
	                <strong>Weeks 5 - 6 90% of an average week's pay</strong>( offset against any statutory maternity pay or maternity allowance payments if applicable) <br />
	                <strong>Weeks 7 - 18 half pay </strong>(plus statutory maternity pay or maternity allowance, to a limit of full pay if applicable) <br />
	                (Weeks 19 - 39 statutory maternity pay or maternity allowance payments if applicable) <br /> 
	                <br />
	                Please note that half pay entitlements are only paid to those that return to employment.</p>";
         } 

         if($form_state['result'][2] == "4.2")
         {
         	$markup = $markup. "
	                <h3>Occupational maternity pay entitlement</h3>
	                <p><strong>Weeks 1 - 4 full pay</strong> (offset against any statutory maternity pay or maternity allowance payments if applicable) <br />
	                <strong>Weeks 5 - 6 90% of an average week's pay</strong>( offset against any statutory maternity pay or maternity allowance payments if applicable) <br />
	                (Weeks 7 - 39 statutory maternity pay or maternity allowance payments if applicable)</p>";
         }       

         if($form_state['result'][2] == "4.3")
         {
         	$markup = $markup. "
	                <h3>Occupational maternity pay entitlement</h3>
	                <p>As you have stated you are unsure about returning to work following your maternity leave you have the following options: <br />
	                <br />
	                <strong>1.</strong>If you return to work you are entitled to: <br />
	                <strong>Weeks 1 - 4 full pay</strong> (offset against any statutory maternity pay or maternity allowance payments if applicable) <br />
	                <strong>Weeks 5 - 6 90% of an average week's pay</strong>( offset against any statutory maternity pay or maternity allowance payments if applicable) <br />
	                <strong>Weeks 7 - 18 half pay </strong>(plus statutory maternity pay or maternity allowance, to a limit of full pay if applicable) <br />
	                (Weeks 19 - 39 statutory maternity pay or maternity allowance payments if applicable) <br /> 
	                <br />
	                <strong>2.</strong>If you do not return to work you are entitled to: <br />
	                <strong>Weeks 1 - 4 full pay</strong> (offset against any statutory maternity pay or maternity allowance payments if applicable) <br />
	                <strong>Weeks 5 - 6 90% of an average week's pay</strong>( offset against any statutory maternity pay or maternity allowance payments if applicable) <br />
	                (Weeks 7 - 39 statutory maternity pay or maternity allowance payments if applicable) <br /> 
	                <br />
	                Please note that half pay entitlements are only paid to those that return to employment. If you remain undecided you can elect to have your 
	                half pay entitlement withheld until your decision has been made.</p>";
         }   


		$markup = $markup. "
	             <h3>Important Dates and Information</h3>
	             <ul>
		             <li>
		             	The earliest date you can start maternity leave is: <strong> {$form_state['result'][5]} </strong>
		             </li>
		             <li>
			             You must tell your manager at least 28 days before you intend to start your maternity leave, however it is preferable
			             before <strong> {$form_state['result'][3]} </strong>
		             </li>
		             <li>
		             	If you are absent from work with a pregnancy related illness on or after <strong> {$form_state['result'][7]} </strong> your maternity leave starts automatically.
		             </li>
	             </ul>

	             <p>This maternity leave page contains further policy information, guidance and frequently asked questions including
	             <a href='http://intranet/directorate/hr/pay_leave_benefits/leave/maternity/Lists/Frequently%20asked%20questions%20for%20employees/DispForm.aspx?ID=3&Source=http%3A%2F%2Fintranet%2Fdirectorate%2Fhr%2Fpay%5Fleave%5Fbenefits%2Fleave%2Fmaternity%2FLists%2FFrequently%2520asked%2520questions%2520for%2520employees%2FAllItems%2Easpx'> what to do next. </a> </p>
	         
	         
	             <strong>Important Dates used to calculate maternity entitlements - beginning of the: </strong><br />
	             <ul>
		             <li>15th week before the baby is due: <strong> {$form_state['result'][3]} </strong> </li>
		             <li>26 weeks before 15th week before the baby is due: <strong> {$form_state['result'][4]} </strong> </li>
		             <li>11th week before the baby is due: <strong> {$form_state['result'][5]} </strong> </li>
		             <li>The week one year before 11th week before the baby is due: <strong> {$form_state['result'][6]} </strong> </li>
	             </ul>
             
             <p><strong>Please note this is an estimate of your entitlement based on the information you have provided, you will be provided written confirmation 
             once your manager has been notified of the details of your pregnancy.</strong></p>";


	}
	else
	{
		$markup = "<strong>{$form_state['result'][0]}</strong>";
	}

	return $markup;
}