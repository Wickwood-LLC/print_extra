<?php

/**
 * Form constructor for the Printer-friendly pages extra module settings form.
 *
 * @ingroup forms
 */
function print_extra_settings() {
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Extra settings'),
  );

  $form['settings']['print_extra_url_list_filter'] = array(
    '#title' => t('URL list filter'),
    '#type' => 'textarea',
    '#description' => t('Enter the internal path for URLs to remove from list at bottom of print and PDF pages. Enter one path per line. The \'*\' character is a wildcard. Example paths are <em>blog</em> for the blog page and <em>blog/*</em> for every personal blog. &lt;front&gt; is the front page. Putting ~ character at beginning of a pattern will make it negation, meaning that path will be included. It will be helpful to include certain sub-pages when parent pages are excluded.'),
    '#default_value' => variable_get('print_extra_url_list_filter', ''),
  );

  return system_settings_form($form);
}

/**
 * Form validation handler for print_extra_settings().
 */
function print_extra_settings_validate($form, &$form_state) {
  global $base_root;

  // Check for a new uploaded logo, and use that instead.
  if ($file = file_save_upload('print_logo_upload', array('file_validate_is_image' => array()))) {
    // The image was saved using file_save_upload() and was added to the
    // files table as a temporary file. We'll make a copy and let the garbage
    // collector delete the original upload.
    if ($filename = file_unmanaged_copy($file->uri)) {
      $wrapper = file_stream_wrapper_get_instance_by_uri($filename);

      $form_state['values']['print_logo_options'] = 2;
      $form_state['values']['print_logo_url'] = str_replace($base_root, '', $wrapper->getExternalUrl());
    }
  }
}