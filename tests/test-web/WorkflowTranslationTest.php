<?php

class WorkflowTranslationTest extends OshaWebTestCase {

  /**
   * Test the content selection screen contains the correct fields & columns.
   */
  public function testNodeContentSelection() {
    $this->loginAsAdmin();

    $this->drupalGet('admin/tmgmt/sources');
    $this->assertRaw('Add to cart');
    $this->assertRaw('Menu link');
    $this->assertRaw('Taxonomy term');
    $this->assertRaw('Literals');
    //@todo: Finish here.
  }

  /**
   * Test adding a node to cart, and check the cart contains the node.
   *
   * 1. Visit node/nid/translate
   * 2. Add to cart
   * 3. Check cart contents at admin/tmgmt/cart
   */
  public function testAddNodeToCart() {
    $this->loginAsAdmin();

    $form_state = array('form_id' => 'tmgmt_entity_ui_translate_form');
    $this->drupalGet('node/4835/translate');
    $this->assertRaw('Add to cart');

    $this->drupalPost('node/4835/translate', $form_state, t('Add to cart'));

    $this->drupalGet('admin/tmgmt/cart');
    $this->assertText('Safety observation in daily use');
  }
}
