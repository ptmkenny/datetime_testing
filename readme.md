CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Usage
 * Requirements
 * Installation
 * Configuration
 * Maintainers

INTRODUCTION
------------

The Datetime Testing module provides an API that helps with developing automated
tests for date and time dependent functionality in Drupal.

It provides the following:

 * Drupal's datetime.time service (which informs Drupal classes about the
   current time) is decorated, adding functions that allow the reported time to
   be altered or frozen.
 * A drop-in replacement for DrupalDateTime (and thus PHP's \Datetime) is
   offered, which respects the current time reported by datetime.time when
   interpreting strings as datetimes.

This is particularly intended to be helpful when writing functional tests,
because the decorated time service uses Drupal's state API to persist manipuated
times across requests. Merely mocking the time service is sufficient for unit
tests but not for functional tests.

USAGE
------------

This is an API-module for developers; it has no effect without custom code.

```

// You can specify the time.
\Drupal::time()->setTime('2008-12-03 09:15pm');
// Returns a timestamp equivalent to '2008-12-03 09:15pm'.
echo \Drupal::time()->getCurrentTime();

// Stop time from flowing, if you like.
\Drupal::time()->freezeTime();
\Drupal::time()->setTime('2008-12-03 09:15pm');
sleep(2);
// Still returns a timestamp equivalent to '2008-12-03 09:15pm'.
echo \Drupal::time()->getCurrentTime();

// Specify a new time using almost anything understood by PHP's strtotime().
// Note that setting the time, even relatively, discards any fractional second
// known for the current time.
\Drupal::time()->setTime('+1 hour);

// The same string parsing logic is available in your own objects
$date = new TestDateTime('+1 hour');

// This will be true.
echo ($date->getTimestamp() === \Drupal::time()->getCurrentTime());

// Now let's allow time to flow again.
\Drupal::time()->unFreezeTime();
sleep(60);
// Now returns a timestamp equivalent to '2008-12-03 09:16pm'.
echo \Drupal::time()->getCurrentTime();

// Return to the normal behavior of datetime.time.
\Drupal::time()->resetTime();
```

See \Drupal\datetime_testing\TestTimeInterface and other classes for further
code documentation.

REQUIREMENTS
------------

Requires Drupal 8.3+.

INSTALLATION
------------

Install as you would normally install a contributed Drupal module.

CONFIGURATION
-------------

There is nothing to configure.

MAINTAINERS
-----------

Current maintainers:
 * Jonathan Shaw (jonathanshaw) - https://drupal.org/u/jonathanshaw

This project has been sponsored by:
 * Awakened Heart Sangha: A UK Buddhist community. Visit https://www.ahs.org.uk for more information.
