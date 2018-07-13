<?php

/**
 * Contains \DatetimeTesting.
 */

use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Behat\Behat\Tester\Exception\PendingException;
use Drupal\DrupalExtension\Context\DrupalSubContextBase;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;

/**
 * Example subcontext.
 */
class DatetimeTesting extends DrupalSubContextBase implements DrupalSubContextInterface {

  /**
   * @var \Drupal\DrupalExtension\Context\DrupalContext
   */
  protected $drupalContext;

  /**
   * @var \Drupal\DrupalExtension\Context\MinkContext
   */
  protected $minkContext;

  /**
   * @BeforeScenario
   */
  public function gatherContexts(BeforeScenarioScope $scope) {
    $environment = $scope->getEnvironment();

    $this->drupalContext = $environment->getContext('Drupal\DrupalExtension\Context\DrupalContext');
    $this->minkContext = $environment->getContext('Drupal\DrupalExtension\Context\MinkContext');
  }

  /**
   * Interpret a string as a datetime, in light of Drupal's current time.
   */
  protected function interpretTime($stringTime) {
    $siteTimezone = \Drupal::config('system.date')->get('timezone.default');

    // Build an interpretation of the string time in light of the current time.
    $currentDate = date_parse(date("Y-m-d H:i:s", \Drupal::time()->getCurrentTime()));
    $parsedDate = date_parse($stringTime);
    // If the year, month or day are not specified, assume the current one.
    $dateParts = ['year', 'month', 'day'];
    foreach ($dateParts as $datePart) {
      if (empty($parsedDate[$datePart])) {
        $parsedDate[$datePart] = $currentDate[$datePart];
      }
    }
    // If no time is given, assume the current time.
    if (empty($parsedDate['hour'])) {
      $parsedDate['hour'] = $currentDate['hour'];
      $parsedDate['minute'] = $currentDate['minute'];
      $parsedDate['second'] = $currentDate['second'];
    }
    else {
      // If an hour is given but no minute or seconds, assume an exact time.
      // i.e. on the exact point of the hour.
      if (empty($parsedDate['minute'])) {
        $parsedDate['minute'] = 0;
      }
      if (empty($parsedDate['second'])) {
        $parsedDate['second'] = 0;
      }
    }

    $parts = [
      'year' => 'Y',
      'month' => 'M',
      'day' => 'D',
      'hour' => 'H',
      'minute' => 'M',
      'second' => 'S',
    ];

    $intervalString = 'P';
    foreach($parts as $part => $letter) {
      if ($part === 'hour') {
        $intervalString .= 'T';
      }
      $increment = 0;
      if (isset($parsedDate['relative'][$part]) && !empty($parsedDate['relative'][$part])) {
          $increment = $parsedDate['relative'][$part];
      }
      $intervalString .= $increment . $letter;
    }
    $interval = new DateInterval($intervalString);    

    if ($parsed[is_localtime]) {
      // A timezone was supplied
    }
    else {
      // Assume the Drupal site timezone.
    }

    return $interpreted;
  }

  /**
   * @Given the time/date/day is :time
   */
  public function timeIs($time) {
  }

  /**
   * @Given :seconds seconds passes
   * @When :seconds seconds passes
   */
  public function secondsPasses($seconds) {
  }


  /**
   * @Then /^I should have a subcontext definition$/
   */
  public function assertSubContextDefinition() {
    throw new PendingException();
  }

}
