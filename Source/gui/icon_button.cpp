/*** MySampler | Source/gui/icon_button.cpp ***/

#include "icon_button.h"

juce::Image BinaryResource::getImage() const
{
    return juce::ImageFileFormat
         ::loadFrom(address, size)
          .convertedToFormat(juce::Image::PixelFormat::RGB);
}

void setButtonIcons(
  ImageButtonPointer& button, 
  juce::Colour color, 
  BinaryResource imageResource,
  std::optional<BinaryResource> clickedImageResource
){
   juce::Image image = imageResource.getImage();
    
   juce::Image clickedImage = clickedImageResource.has_value()
                            ? clickedImageResource.value().getImage()
                            : juce::Image();

    button->setImages(
        true,            // resizeButtonNowToFitThisImage
        true,            // rescaleImagesWhenButtonSizeChanges
        true,            // preserveImageProportions
        image,           // normal image
        1.0,             // imageOpacityWhenNormal
        color,           // overlayColourWhenNormal
        image,           // overImage
        0.5,             // imageOpacityWhenOver
        color,           // overlayColourWhenOver
        clickedImage,    // downImage
        1.0,             // imageOpacityWhenDown
        color,           // overlayColourWhenDown
        false            // hitTestAlphaThreshold
    );
}

void setButtonIcon(ImageButtonPointer& button, juce::Colour color, BinaryResource resource)
{
    return setButtonIcons(button, color, resource, std::nullopt);
}

void setToggleButtonIcons(
    ImageButtonPointer& button,
    juce::Colour color,
    BinaryResource upImageResource,
    BinaryResource downImageResource)
{
    setButtonIcons(button, color, upImageResource, std::make_optional(downImageResource));
}
