<?php

/**
 * @file
 * Views hooks for Commerce Stock History.
 */

/**
 * Implements hook_views_data_alter().
 */
function commerce_stock_history_views_data_alter(&$data) {
  $data['commerce_stock_history']['table']['join'] = array(
    'commerce_product' => array(
      'left_field' => 'product_id',
      'field' => 'product_id',
    ),
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

  $data['commerce_stock_history']['product_id']['relationship'] = array(
    'base' => 'commerce_product',
    'base field' => 'product_id',
    'handler' => 'views_handler_relationship',
    'label' => t('Product'),
    'title' => t('Commerce product.'),
    'help' => t('The product that the stock history entry is for.'),
  );

  $data['commerce_stock_history']['uid']['relationship'] = array(
    'base' => 'users',
    'base field' => 'uid',
    'handler' => 'views_handler_relationship',
    'label' => t('User'),
    'title' => t('User'),
    'help' => t('The user that the stock history entry was created by.'),
  );
}
