<?php

class WorkflowPublicationTest extends OshaWebTestCase {

  /**
   * Test access to the project managers configuration per section.
   */
  public function testProjectManagersScreen() {
    $this->loginAsAdmin();

    $pms = osha_workflow_access_pm_get_pm('main-menu', 'menu');
    if (!empty($pms)) {
      reset($pms);
      $pm = current($pms);
      $this->drupalGet('admin/config/workbench/access/managers');
      $this->assertText('Main menu');
      $options = array( "users[{$pm->uid}][remove]" => 1 );
      $this->drupalPost('admin/config/workbench/access/managers/menu/main-menu', $options, t('Update Project Manager'));
      $this->assertText('No active project managers have been found.');
    }

    $pm2 = user_load_by_name('project_manager2');
    $options = array("add_user" => $pm2->uid);
    $this->drupalPost('admin/config/workbench/access/managers/menu/main-menu', $options, t('Update Project Manager'));

    $this->drupalGet('admin/config/workbench/access/managers/menu/main-menu');
    $this->assertText('project_manager2');
  }
}
