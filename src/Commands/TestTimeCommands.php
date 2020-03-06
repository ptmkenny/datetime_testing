<?php

declare(strict_types = 1);

namespace Drupal\datetime_testing\Commands;

use Drupal\Core\Datetime\DrupalDateTime;
use Drupal\datetime_testing\TestTimeInterface;
use Drush\Commands\DrushCommands;

/**
 * Provide Drush commands for the test time service.
 */
class TestTimeCommands extends DrushCommands {

  /**
   * Mock request time manager service.
   *
   * @var \Drupal\datetime_testing\TestTimeInterface
   */
  protected $testTime;

  /**
   * MockRequestTimeCommands constructor.
   *
   * @param \Drupal\datetime_testing\TestTimeInterface $test_time
   *   Test time service.
   */
  public function __construct(TestTimeInterface $test_time) {
    parent::__construct();
    $this->testTime = $test_time;
  }

  /**
   * Set test time.
   *
   * @param string $time
   *   Date and time to be set, in the following format 'Y-m-d H:i:s'.
   *
   * @usage datetime-testing:set '2020-01-15 12:00:00'
   *
   * @command datetime-testing:set
   */
  public function set(string $time): void {
    $timestamp = DrupalDateTime::createFromFormat(DrupalDateTime::FORMAT, $time)->getTimestamp();
    $this->testTime->setTime($timestamp);
    $this->logger()->success("Time has been set to '{$time}', timestamp: {$timestamp}.");
  }

  /**
   * Get current time.
   *
   * @usage datetime-testing:get
   *
   * @command datetime-testing:get
   */
  public function get(): void {
    $time = $this->testTime->getCurrentTime();
    $date = DrupalDateTime::createFromTimestamp($time)->format(DrupalDateTime::FORMAT);
    $this->logger()->success("Current time value is {$date}, timestamp: {$time}.");
  }

  /**
   * Freeze test time.
   *
   * @command datetime-testing:freeze
   */
  public function freeze(): void {
    $this->testTime->freezeTime();
    $time = $this->testTime->getCurrentTime();
    $date = DrupalDateTime::createFromTimestamp($time)->format(DrupalDateTime::FORMAT);
    $this->logger()->success("Time is frozen to {$date}, timestamp: {$time}.");
  }

  /**
   * Get current time.
   *
   * @command datetime-testing:get
   */
  public function unfreeze(): void {
    $this->testTime->freezeTime();
    $this->logger()->success("Time has been unfrozen.");
  }

  /**
   * Reset test time.
   *
   * @usage datetime-testing:reset
   *
   * @command datetime-testing:reset
   */
  public function reset(): void {
    $this->testTime->resetTime();
    $this->logger()->success("Test time has been reset.");
  }

}
