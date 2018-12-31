<?php

/**
 * Copied from contxt module's match method in plugins/context_condition_path.inc
 *
 * Match the subject against a set of regex patterns.
 * Similar to drupal_match_path() but also handles negation through the use
 * of the ~ character.
 *
 * @param mixed $subject
 *   The subject string or an array of strings to be matched.
 * @param array $patterns
 *   An array of patterns. Any patterns that begin with ~ are considered
 *   negative or excluded conditions.
 */
function print_extra_match_path($subject, $patterns) {
  static $regexps;
  $match = FALSE;
  $positives = $negatives = 0;
  $subject = !is_array($subject) ? array($subject) : $subject;
  foreach ($patterns as $pattern) {
    if (strpos($pattern, '~') === 0) {
      $negate = TRUE;
      $negatives++;
    }
    else {
      $negate = FALSE;
      $positives++;
    }
    $pattern = ltrim($pattern, '~');
    if (!isset($regexps[$pattern])) {
      $regexps[$pattern] = '/^(' . preg_replace(array('/(\r\n?|\n)/', '/\\\\\*/', '/(^|\|)\\\\<front\\\\>($|\|)/'), array('|', '.*', '\1' . preg_quote(variable_get('site_frontpage', 'node'), '/') . '\2'), preg_quote($pattern, '/')) . ')$/';
    }
    foreach ($subject as $value) {
      if (preg_match($regexps[$pattern], $value)) {
        if ($negate) {
          return FALSE;
        }
        $match = TRUE;
      }
    }
  }
  // If there are **only** negative conditions and we've gotten this far none
  // we actually have a match.
  if ($positives === 0 && $negatives) {
    return TRUE;
  }
  return $match;
}
