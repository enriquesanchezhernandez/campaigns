<?php
/**
 * @file
 * Simple test that shows that PHPUnit works.
 */

/**
 * Author: Cristian Romanescu <cristi _at_ eaudeweb dot ro>
 * Created: 201412151936
 */

class FrameworkBootstrapTest extends OshaWebTestCase {

  /**
   * Test Drupal API availability.
   */
  public function testBootstrap() {
    $this->assertNotNull(user_load(1));
  }

  /**
   * Test administrator login.
   */
  public function testLogin() {
    $this->loginAsAdmin();
    $this->drupalGet('admin/config');
    $this->assertText('Multilingual settings');
  }
}
