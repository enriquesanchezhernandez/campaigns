<?php
/**
 * Controller.php
 * Abstract class for controllers
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 */
abstract class Controller {
    /**
     * @var Model object
     */
    protected $model;
    /**
     * @var Direct output or return
     */
    protected $directOutput;

    /**
     * Execute an action defined in the specific controller
     */
    public function executeAction() {
        $params = Parameters::getInstance();
        $action  = $params->get('action');
        if (method_exists($this, $action)) {
            $this->$action();
        }
    }

    /**
     * Attributes validation
     */
    protected function validateAttribute() {
        $ret = true;
        if ($this->model) {
            $param = Parameters::getInstance();
            $attribute = $param->get('attribute');
            $value = $param->get('value');
            $this->model->set($attribute, $value);
            $ret = $this->model->validate($attribute);
        }
        if ($param->get('ajax')) {
            $messageBus = MessageBus::getInstance();
            $response = array(
                'status' => $ret,
                'id' => $attribute,
                'message' => $messageBus->getMessage($attribute),
            );
            print json_encode($response);
            die;
        } else {
            return $ret;
        }
    }

    /**
     * Download a PDF file
     * @param string $content
     * @param string $controller
     */
    protected function pdf($content = '', $controller = '') {
        if (!empty($content)) {
            $pdf = new Pdf();
            $path = $pdf->render($content);
            File::download($controller . '-' . date('d-m-Y_H-i'), $path, 'application/pdf');
        }
    }
}