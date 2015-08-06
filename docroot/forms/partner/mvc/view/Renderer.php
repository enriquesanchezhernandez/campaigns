<?php
/**
 * Render a view
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 */
class Renderer {
    private $basePath;
    private $baseUrl;
    private $cssPath;
    private $cssUrl;
    private $htmlHeaderTpl;
    private $htmlFooterTpl;
    private $cachePath;
    private $headerTpl;
    private $footerTpl;
    private $bodyTpl;
    private $includeHeaderFooter;

    /**
     * Class constructor
     * @param $view
     */
    public function __construct($view, $includeHeaderFooter = true) {
        $params = Parameters::getInstance();
        $this->basePath = APP_ROOT . $params->get('viewPath');
        $this->baseUrl = APP_URL . $params->get('viewPath');
        $this->cssPath = APP_ROOT . $params->get('cssPath');
        $this->cssUrl = APP_URL . $params->get('cssPath');
        $this->jsPath = APP_ROOT . $params->get('jsPath');
        $this->jsUrl = APP_URL . $params->get('jsPath');
        $this->htmlHeaderTpl = $params->get('htmlHeaderTpl');
        $this->htmlFooterTpl = $params->get('htmlFooterTpl');
        $this->cachePath = $params->get('cachePath');
        $this->headerTpl = $params->get('headerTpl');
        $this->footerTpl = $params->get('footerTpl');
        $this->bodyTpl = strtolower($view . '.html');
        $this->includeHeaderFooter = $includeHeaderFooter;
    }

    /**
     * Generate the header/footer
     * @param $dwoo
     * @param $tpl
     * @return bool|string
     */
    private function renderPart($dwoo, $tpl) {
        return $dwoo->get($this->basePath . $tpl);
    }

    /**
     * Insert the default header
     * @param $dwoo
     * @param $printable
     * @return mixed
     */
    private function renderHtmlHeader($dwoo, $printable = false) {
        $content = array(
            'css' => File::browseDirectory($this->cssPath, '.css', $this->cssUrl),
            'js' => File::browseDirectory($this->jsPath, '.js', $this->jsUrl)
        );
        if (!$printable) {
            $value = $this->cssUrl . 'print.css';
            if(($key = array_search($value, $content['css'])) !== false) {
                unset($content['css'][$key]);
            }
        }
        return $dwoo->get($this->basePath . $this->htmlHeaderTpl, $content);
    }

    /**
     * Insert the default footer
     * @param $dwoo
     * @return mixed
     */
    private function renderHtmlFooter($dwoo) {
        return $dwoo->get($this->basePath . $this->htmlFooterTpl);
    }

    /**
     * String encoding
     * @param $string
     * @return array|string
     */
    private function utf8Encode($string)
    {
        if (is_array($string)) {
            foreach ($string as $key => &$value) {
                $value = $this->utf8Encode($value);
            }
            $ret = $string;
        } elseif (is_a($string, 'stdClass')) {
            $ret = $this->utf8Encode(get_object_vars($string));
        } else {
            $ret = utf8_encode($string);
        }

        return $ret;
    }

    /**
     * Render the content
     * @param null $contentArray
     * @return string
     */
    public function render($contentArray = null) {
        // Register Dwoo namespace and register autoloader
        $dwoo = new Dwoo();
        if (isset($contentArray)) {
            if (is_array($contentArray)) {
                foreach ($contentArray as $key => &$value) {
                    $value = $this->utf8Encode($value);
                }
            } else {
                $contentArray = $this->utf8Encode($contentArray);
            }
            $content = $dwoo->get($this->basePath . $this->bodyTpl, $contentArray);
        }
        if ($this->includeHeaderFooter) {
            $printable = isset($contentArray['print']) || isset($contentArray['pdf']) ? true : false;
            $htmlHeader = $this->renderHtmlHeader($dwoo, $printable);
            $htmlFooter = $this->renderHtmlFooter($dwoo);
            $header = $this->renderPart($dwoo, $this->headerTpl);
            $footer = $this->renderPart($dwoo, $this->footerTpl);
        } else {
            $htmlHeader = $htmlFooter = $header = $footer = '';
        }
        $content = $htmlHeader . $header. $content . $footer . $htmlFooter;
        return $content;
    }
}