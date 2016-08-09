<?php

/**
 * @file
 * Rules hooks and callbacks for Commerce Stock History.
 */

/**
 * Implements hook_rules_action_info().
 */
function commerce_stock_history_rules_action_info() {
  return array(
    'commerce_stock_history_create_by_line_item' => array(
      'label' => t('Create a stock history entry, given a line item'),
      'parameter' => array(
        'line_item' => array(
          'type' => 'commerce_line_item',
          'label' => t('Line item'),
        ),
        'message' => array(
          'type' => 'text',
          'label' => t('Message'),
          'default mode' => 'direct',
        ),
        'quantity' => array(
          'type' => 'integer',
          'label' => t('Quantity'),
        ),
        'uid' => array(
          'type' => 'integer',
          'label' => t('User ID'),
          'optional' => TRUE,
        ),
      ),
      'group' => t('Commerce stock history'),
    ),
  );
}

/**
 * Rules action: creates a stock history entry using a commerce line item.
 */
function commerce_stock_history_create_by_line_item($line_item, $message, $quantity, $uid = -1) {
  if ($uid === -1) {
    global $user;
    $uid = $user->uid;
  }

  if (in_array($line_item->type, commerce_product_line_item_types())) {
    $sku = $line_item->line_item_label;
    $product = commerce_product_load_by_sku($sku);

    if (commerce_ss_product_type_enabled($product->type)) {
      $override_enabled_type = commerce_ss_product_type_override_enabled($product->type);
      $override_enabled_product = isset($product->commerce_stock_override['und']) && $product->commerce_stock_override['und'][0]['value'] == 1;

      if (!($override_enabled_type && $override_enabled_product)) {
        commerce_stock_history_create_entry($message, $product, $quantity, $uid);
      }
    }
  }
}
