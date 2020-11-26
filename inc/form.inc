<?php
namespace TLA\FLAT\CmdiTemplates;

use TLA\FLAT\CmdiTemplates\Exceptions\InvalidTemplateException;
use FormBuilder as FlatDepositFormBuilder;
use CmdiHandler;

/**
 * Building form component based on cmdi template block
 * chosen to be loaded
 *
 * @author  Ibrahim Abdullah <ibrahim.abdullah@mpi.nl>
 * @package TLA Flat
 */
class FormBuilder
{
    /**
     * @param string $template
     */
    public function __construct($template)
    {
        $this->template = $this->loadTemplate($template);
    }

    public function getComponent($nodeName, $data)
    {
        $foundComponent = null;

        foreach ($this->template->items->item as $component) {

            if ($nodeName === (string)$component['name']) {

                $foundComponent = $component;
                break;
            }
        }

        if (null === $foundComponent) {
            throw new InvalidTemplateException('Template ' . $name . ' does not contain ' . $nodeName);
        }

        return $this->generateFormElement($foundComponent, $data);
    }

    /**
     * Generating form element
     *
     * @param
     */
    private function generateFormElement($component, $data)
    {
        $class          = 'Form' . (string)$component['type'];
        $numberElements = isset($component['minOccurrence']) ? (int)$component['minOccurrence'] : 0;
        $element        = new $class($numberElements);

        $element->setFormComponent($component, $data, null, 0, true);

        return $element->getFormComponent();
    }

    /**
     * Loading template
     *
     * @param string $name
     *
     * @return SimpleXMLElement
     * @throws InvalidTemplateException
     */
    private function loadTemplate($name)
    {
        $filename = FlatDepositFormBuilder::FORM_TEMPLATES_PATH . $name . '.xml';
        $template = simplexml_load_file($filename);

        if (!$template){
            throw new InvalidTemplateException('Template ' . $name . ' could not be loaded');
        }

        if (!isset($template->items)) {
            throw new InvalidTemplateException('Template ' . $name . ' was invalid');
        }

        return $template;
    }
}
