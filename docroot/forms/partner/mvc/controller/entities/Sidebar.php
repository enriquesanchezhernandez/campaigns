<?php
/**
 * Sidebar.php
 * Controller for the sidebar
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 */
class Sidebar extends Controller implements IController {
    /**
     * Class controller
     * @param bool  $directOutput
     */
    public function __construct($directOutput = false) {
        $this->directOutput = $directOutput;
    }

    /**
     * Retrieve the class name
     * @return string
     */
    public static function getName() {
        return strtolower(__CLASS__);
    }

    /**
     * Execute the controller
     */
    public function execute() {
        $params = Parameters::getInstance();
        $renderer = new Renderer('sidebar', false);
        $renderer->setViewPath($params->get('viewEntitiesPath'));
        $contentArray = array(
            'appurl' => APP_URL . '?route=' . $params->get('route'),
            'appurlsidebar' => APP_URL,
            'title' => $params->get('title'),
            'sections' => $this->getSections(),
            'session_id' => $params->getUrlParamValue('session_id'),
            'partner_type' => $params->getUrlParamValue('partner_type'),
            'locked' => $params->getUrlParamValue('locked'),
            'mf' => $params->getUrlParamValue('maintenance_mode'),
        );
        $content = $renderer->render($contentArray);
        if ($this->directOutput) {
            print $content;
        } else {
            return $content;
        }
    }

    /**
     * Retrieve the current sections
     * @return array
     */
    private function getSections() {
        $params =  Parameters::getInstance();
        $entity = $params->getUrlParamValue('entity');
        $routes = $params->get('routes');
        $entitiesPath = $params->get('entitiesPath');
        foreach ($routes as $route => $routeData) {
            $entityFile = APP_ROOT . $entitiesPath . $entity . '_' . $route;
            if ($content = File::read($entityFile)) {
                $content = json_decode($content, true);
                $content = isset($content['sections']) ?  $content['sections'] : '';
                if ($content && isset($content['title']) && isset($content['sections'])) {
                    $sections[] = array(
                        'title' => $content['title'],
                        'route' => $route,
                        'sections' => $content['sections'],
                    );
                }
            }
        }
        return $sections;
    }
}