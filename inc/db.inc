<?php

/**
 * db error was found, send drupal message to show what
 * went wrong
 *
 * @param Exception $e
 */
function flat_cmdi_temlates_db_error(Exception $e) {

  if ($e->errorInfo[0] == '42P01') {
      drupal_set_message(t('Flat Cmdi Templates table not found. Try running <a href="@update_url">update.php</a>.', ['@update_url' => url('update.php')]), 'error');
  } else {
      drupal_set_message($e->getMessage(), 'error');
  }
}

/**
 * save cmdi template block to db
 *
 * @param string $filename
 * @param string $label
 * @param string $containerName
 * @param string $node
 * @param string $template
 *
 * @return boolean
 */
function flat_cmdi_templates_db_save($filename, $label, $containerName, $node, $template) {

  try {

    db_insert('flat_cmdi_templates')
      ->fields([
        'filename'  => $filename,
        'label'     => $label,
        'container' => $containerName,
        'node'      => $node,
        'template'  => $template,
      ])
    ->execute();

    return true;

  } catch (Exception $e) {

    flat_cmdi_temlates_db_error($e);
    return false;
  }
}

/**
 * Fetching all templates
 *
 * @param string $filename
 *
 * @return boolean
 */
function flat_cmdi_templates_db_fetch_all($filename) {

  return db_select('flat_cmdi_templates', 'fct')
        ->fields('fct')
        ->condition('filename', $filename, '=')
        ->execute()
        ->fetchAllAssoc('id', PDO::FETCH_ASSOC);
}

/**
 * Fetching specific template
 *
 * @param string $id
 *
 * @return boolean
 */
function flat_cmdi_templates_db_fetch($id) {

  return db_select('flat_cmdi_templates', 'fct')
        ->fields('fct')
        ->condition('id', $id, '=')
        ->execute()
        ->fetchAssoc('id', PDO::FETCH_ASSOC);
}
