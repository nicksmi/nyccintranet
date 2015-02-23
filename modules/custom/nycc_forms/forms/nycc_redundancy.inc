<?php

function redundancy_calc_form($form, &$form_state) {
  
   // If the form has been submitted, output something related to the submission
  if ($form_state['submitted'] && $form_state['values']['submit_button'] != 'Re-calculate') 
  {
    $form['submission'] = array(
      '#markup' => redundancy_calc_results_output($form_state));

	$form['#attributes'] = array('class' => array('form-results'));


	$form['submit_button'] = array(
	'#type' => 'submit',
	'#value' => t('Re-calculate'),
  	);

  }
  else {
    // Otherwise build the normal form

	$form['name'] = array(
	    '#type' => 'textfield', 
	    '#title' => 'Your name',
	    '#size' => 50,
	    '#maxlength' => 50,
	    '#required' => TRUE, 
	  );

	if (isset($form_state['storage']['name'])) {
	  $form['name']['#default_value'] = $form_state['storage']['name'];
	}


	$form['dateofbirth'] = array(
	    '#type' => 'date', 
	    '#title' => 'Your date of birth',
	    '#required' => TRUE, 
	  );

	if (isset($form_state['storage']['dateofbirth'])) {
	  $form['dateofbirth']['#default_value'] = $form_state['storage']['dateofbirth'];
	}

	$form['dateofleaving'] = array(
	    '#type' => 'date', 
	    '#title' => 'Your date of leaving the council',
	    '#required' => TRUE, 
	  );

	if (isset($form_state['storage']['dateofleaving'])) {
	  $form['dateofleaving']['#default_value'] = $form_state['storage']['dateofleaving'];
	}

	$form['datecontinuousemp'] = array(
	    '#type' => 'date', 
	    '#title' => 'The date you commenced continuous employment',
	    '#required' => TRUE, 
	  );

	if (isset($form_state['storage']['datecontinuousemp'])) {
	  $form['datecontinuousemp']['#default_value'] = $form_state['storage']['datecontinuousemp'];
	}

	$employeetypeoptions = array('teacher' => t('Yes I’m a teacher'), 'supportstaff' => t('Yes I’m support staff'), 'another' => t('No I\'m a centrally employed teacher'), 'no' => t('No'));

	$form['employeetype'] = array(
	'#type' => 'radios',
	'#title' => t('Are you employed by an NYCC school?'),
	'#default_value' => 'no',
	'#options' => $employeetypeoptions,
	'#required' => TRUE, 
	);

	if (isset($form_state['storage']['employeetype'])) {
	  $form['employeetype']['#default_value'] = $form_state['storage']['employeetype'];
	}

	$teacherestimateoptions = array('voluntary' => t('I require a voluntary redundancy estimate'), 'compulsory' => t('I require a compulsory redundancy estimate'), 'both' => t('I require both a compulsory and voluntary redundancy estimate'));

	$form['teacherestimate'] = array(
	'#type' => 'radios',
	'#title' => t('As a teacher, what would you like to estimate?'),
	'#default_value' => 'voluntary',
	'#options' => $teacherestimateoptions,
	    '#states' => array(
	      'visible' => array(
	        array(
	          ':input[name="employeetype"]' => array(
	            array("value" => 'teacher'),
	          ),
	        ),
	      ),
	      'required' => array(
	        array(
	          ':input[name="employeetype"]' => array(
	            array("value" => 'teacher'),
	          ),
	        ),
	      ),	      
	      ),
  	);

	if (isset($form_state['storage']['teacherestimate'])) {
	  $form['teacherestimate']['#default_value'] = $form_state['storage']['teacherestimate'];
	}

	$form['annualsalary'] = array(
	    '#type' => 'textfield', 
	    '#title' => 'Annual full time salary (£):',
	    '#size' => 10,
	    '#maxlength' => 10,
	    '#required' => TRUE, 
	  );

	if (isset($form_state['storage']['annualsalary'])) {
	  $form['annualsalary']['#default_value'] = $form_state['storage']['annualsalary'];
	}

	$form['totalmonthlyallowances'] = array(
	    '#type' => 'textfield', 
	    '#title' => 'Total monthly allowances (£):',
	    '#size' => 10,
	    '#maxlength' => 10,
	    '#required' => TRUE, 
	  );

	if (isset($form_state['storage']['totalmonthlyallowances'])) {
	  $form['totalmonthlyallowances']['#default_value'] = $form_state['storage']['totalmonthlyallowances'];
	}

	$form['contractedhours'] = array(
	    '#type' => 'textfield', 
	    '#title' => 'Contracted hours (please enter between 1 and 37):',
	    '#size' => 4,
	    '#maxlength' => 4,
	    '#states' => array(
	      'visible' => array(
	        array(
	          ':input[name="employeetype"]' => array(
	            array("value" => 'no'),
	            array("value" => 'supportstaff'),
	          ),
	        ),
	      ),
	      'required' => array(
	        array(
	          ':input[name="employeetype"]' => array(
	            array("value" => 'no'),
	            array("value" => 'supportstaff'),
	          ),
	        ),
	      ),	      
	      ),
  	);

	if (isset($form_state['storage']['contractedhours'])) {
	  $form['contractedhours']['#default_value'] = $form_state['storage']['contractedhours'];
	}

	$form['fte'] = array(
	    '#type' => 'textfield', 
	    '#title' => 'FTE (please enter a value between 0 and 1 eg. 0.35):',
	    '#size' => 4,
	    '#maxlength' => 4,
	    '#states' => array(
	      'visible' => array(
	        array(
	          ':input[name="employeetype"]' => array(
	            array("value" => 'another'),
	            array("value" => 'teacher'),
	          ),
	        ),
	      ),
	      'required' => array(
	        array(
	          ':input[name="employeetype"]' => array(
	            array("value" => 'another'),
	            array("value" => 'teacher'),
	          ),
	        ),
	      ),	      
	      ),
  	);

	if (isset($form_state['storage']['fte'])) {
	  $form['fte']['#default_value'] = $form_state['storage']['fte'];
	}

	$form['submit_button'] = array(
	'#type' => 'submit',
	'#value' => t('Submit'),
  	);

 }
  return $form;
}


function redundancy_calc_form_validate($form, &$form_state) {

	if ($form_state['values']['submit_button'] != 'Re-calculate') 
	{
		if (!($form_state['values']['annualsalary'] > 0)){
		form_set_error('annualsalary', t('Salary must be a positive number.'));
		}

		if (!is_numeric($form_state['values']['totalmonthlyallowances'])){
		form_set_error('totalmonthlyallowances', t('Allowances must be a number.'));
		}	  


		if(($form_state['values']['employeetype'] == 'no') || ($form_state['values']['employeetype'] == 'supportstaff'))
		{
			if (($form_state['values']['contractedhours'] < 1) || ($form_state['values']['contractedhours'] > 37) ){
			form_set_error('contractedhours', t('Contracted hours must be between 1 and 37'));
			}	
		}
		

		if(($form_state['values']['employeetype'] == 'another') || ($form_state['values']['employeetype'] == 'teacher'))
		{
			if (($form_state['values']['fte'] < 0) || ($form_state['values']['fte'] > 1) || (!is_numeric($form_state['values']['fte'])) ){
				form_set_error('fte', t('FTE must be between 0 and 1'));
			}	
		}

	}
}


function redundancy_calc_form_submit($form, &$form_state) {
	
	if ($form_state['values']['submit_button'] != 'Re-calculate') 
	{

	$form_state['results'] = array(
	    'ageatleaving' => 0, 
	    'fullyearsservice' => 0,
	    'entitlement' => 0,
	    'fullweeklyrate' => 0,
	    'compulsoryweeklyrate' => 0,
	    'estimateofvoluntary' => 0, 
	    'estimateofcompulsory' => 0, 
	    'estimateofredundancy' => 0,
	  );

	//Create the redundancy calc service ref
	$service = wsclient_service_load('redundancy_calculator');

	//Sort out all the submitted dates
	$dobStr = $form_state['values']['dateofbirth']['year'] . '-' . $form_state['values']['dateofbirth']['month'] . '-' . $form_state['values']['dateofbirth']['day'];
	$dob = date('Y-m-d', strtotime($dobStr));


	$leavingStr = $form_state['values']['dateofleaving']['year'] . '-' . $form_state['values']['dateofleaving']['month'] . '-' . $form_state['values']['dateofleaving']['day'];
	$leaving = date('Y-m-d', strtotime($leavingStr));


	$continuousStr = $form_state['values']['datecontinuousemp']['year'] . '-' . $form_state['values']['datecontinuousemp']['month'] . '-' . $form_state['values']['datecontinuousemp']['day'];
	$continuous = date('Y-m-d', strtotime($continuousStr));


	//Build the request for GetAgeAtLeaving
	$AgeAtLeavingReq = array('parameters' => array('AgeAtLeavingReq' => array('dateOfBirth' => $dob,
		'leaveDate' => $leaving)));

	//Make the call
	$response = $service->invoke('GetAgeAtLeaving', $AgeAtLeavingReq);

	$form_state['results']['ageatleaving'] = $response->AgeAtLeavingResp->ageAtLeaving;



	//Build the request for GetFullYearsService
	$FullYrsServiceReq = array('parameters' => array('FullYrsServiceReq' => array('startdate' => $continuous,
		'leaveDate' => $leaving)));

	//Make the call
	$response = $service->invoke('GetFullYearsService', $FullYrsServiceReq);

	$form_state['results']['fullyearsservice'] = $response->FullYrsServiceResp->yrsService;



	//Build the request for GetWksEntitlement
	$WksEntitlementReq = array('parameters' => array('WksEntitlementReq' => array('ageAtLeaving' => $form_state['results']['ageatleaving'],
		'yrsService' => $form_state['results']['fullyearsservice'])));

	//Make the call
	$response = $service->invoke('GetWksEntitlement', $WksEntitlementReq);

	$form_state['results']['entitlement'] = $response->WksEntitlementResp->wksEntitlement;



	//Build the request for FullWklyRateReq
	if($form_state['values']['employeetype'] == "supportstaff" || $form_state['values']['employeetype'] == "no")
	{
		$FullWklyRateReq = array('parameters' => array('FullWklyRateReq' => array('empType' => 'E',
		'salary' => $form_state['values']['annualsalary'], 'allowances' => $form_state['values']['totalmonthlyallowances'], 'proportion' => $form_state['values']['contractedhours'])));
	}
	else
	{
		$FullWklyRateReq = array('parameters' => array('FullWklyRateReq' => array('empType' => 'teacher',
		'salary' => $form_state['values']['annualsalary'], 'allowances' => $form_state['values']['totalmonthlyallowances'], 'proportion' => $form_state['values']['fte'])));
	}

	//Make the call
	$response = $service->invoke('GetFullWklyRate', $FullWklyRateReq);

	$form_state['results']['fullweeklyrate'] = $response->FullWklyRateResp->fullWklyRate;



	//Build the request for GetLimitedWklyRate
	$LimitedWklyRateReq = array('parameters' => array('LimitedWklyRateReq' => array('salary' => $form_state['values']['annualsalary'],
		'allowances' => $form_state['values']['totalmonthlyallowances'], 'proportion' => $form_state['values']['fte'], 'leaveDate' => $leaving)));

	//Make the call
	$response = $service->invoke('GetLimitedWklyRate', $LimitedWklyRateReq);

	$form_state['results']['compulsoryweeklyrate'] = $response->LimitedWklyRateResp->limitedWklyRate;

	$form_state['results']['estimateofvoluntary'] = $form_state['results']['entitlement'] * $form_state['results']['fullweeklyrate'];

	$form_state['results']['estimateofcompulsory'] = $form_state['results']['entitlement'] * $form_state['results']['compulsoryweeklyrate'];

	$form_state['results']['estimateofredundancy'] = $form_state['results']['entitlement'] * $form_state['results']['fullweeklyrate'];

/*
	try 
	{
		$results['ageatleaving'] = $service->GetAgeAtLeaving($dob, $dateofleaving);
	}
	catch (WSClientException $e) 
	{
	watchdog('wsclient', $e->__toString());

	}
*/

	$form_state['storage']['name'] = $form_state['values']['name'];
	$form_state['storage']['dateofbirth'] = $form_state['values']['dateofbirth'];
	$form_state['storage']['dateofleaving'] = $form_state['values']['dateofleaving'];
	$form_state['storage']['datecontinuousemp'] = $form_state['values']['datecontinuousemp'];
	$form_state['storage']['employeetype'] = $form_state['values']['employeetype'];
	$form_state['storage']['teacherestimate'] = $form_state['values']['teacherestimate'];
	$form_state['storage']['annualsalary'] = $form_state['values']['annualsalary'];
	$form_state['storage']['totalmonthlyallowances'] = $form_state['values']['totalmonthlyallowances'];
	$form_state['storage']['contractedhours'] = $form_state['values']['contractedhours'];
	$form_state['storage']['fte'] = $form_state['values']['fte'];
	}

	$form_state['rebuild'] = TRUE;

}


function redundancy_calc_results_output(&$form_state) {

	$markup = "
	<h2>Redundancy estimate for {$form_state['values']['name']}</h2>
	<span>Age at proposed date of leaving:</span>
	<div>{$form_state['results']['ageatleaving']}</div>
	<span>Total of completed years service at proposed date of leaving:</span>
	<div>{$form_state['results']['fullyearsservice']}</div>
	";

	if($form_state['values']['employeetype'] == 'teacher')
	{
		if($form_state['values']['teacherestimate'] == 'voluntary' || $form_state['values']['teacherestimate'] == 'both')
		{
			$markup = $markup."
			<h2>Voluntary redundancy</h2>
			<span>Voluntary weekly rate of pay (a): (£)</span>
			<div>{$form_state['results']['fullweeklyrate']}</div>
			<span>Weeks pay entitlement (b):<span>
			<div>{$form_state['results']['entitlement']}</div>
			<span>Estimate of voluntary redundancy (a) x (b): (£)<span>
			<div>{$form_state['results']['estimateofvoluntary']}</div>
			";	
		}

		if($form_state['values']['teacherestimate'] == 'compulsory' || $form_state['values']['teacherestimate'] == 'both')
		{
			$markup = $markup."
			<h2>Compulsory redundancy</h2>
			<span>Compulsory weekly rate of pay (a): (£)</span>
			<div>{$form_state['results']['compulsoryweeklyrate']}</div>
			<span>Weeks pay entitlement (b):<span>
			<div>{$form_state['results']['entitlement']}</div>
			<span>Estimate of compulsory redundancy (a) x (b): (£)<span>
			<div>{$form_state['results']['estimateofcompulsory']}</div>
			";	
		}



		$markup = $markup."
		<div>
			<p>
				This estimate cannot be construed as either an approval or an offer from North Yorkshire County Council and is for general information purposes only.
			</p>
		</div>
		";

	}
	else
	{
		$markup = $markup."
		<span>Weeks pay entitlement (a):</span>
		<div>{$form_state['results']['entitlement']}</div>
		<span>Weekly rate of pay (b): (£)</span>
		<div>{$form_state['results']['fullweeklyrate']}</div>	


		<h2>Estimate of redundancy (a) x (b) £{$form_state['results']['estimateofredundancy']}</h2>
		<p>
			This estimate cannot be construed as either an approval or an offer from North Yorkshire County Council and is for general information purposes only.
		</p>
		";		

		if($form_state['values']['employeetype'] == "supportstaff" || $form_state['values']['employeetype'] == "no")
		{
			$markup = $markup."
				<h2>Pension strain costs</h2>
	            <p>Please note the following, (which is not relevant to members of the Teachers' Pension Scheme):-</p>
	            <p>Members of the Local Government Pensions Scheme who are made redundant aged 55 or over are automatically 
	                entitled to the immediate payment of their pension. This creates additional 
	                costs that the Authority must recompense the pension scheme for. The cost of termination 
	                (redundancy payments and pension strain costs) is a factor that must be taken into account in selection 
	                for redundancy including decisions on voluntary redundancy applications.
	            </p>
			";		
		}

	}

	return $markup;
}