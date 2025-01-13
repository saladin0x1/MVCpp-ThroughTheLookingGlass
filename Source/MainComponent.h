//------- Include Guards -------
#pragma once

//------- Includes -------
#include <JuceHeader.h>
#include "Model.h"
#include "HomeComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::Component
{
public:
    //==============================================================================
    // Constructor
    MainComponent();

    // Destructor
    ~MainComponent() override;

    //==============================================================================
    // Paint method: Handles custom drawing
    void paint(juce::Graphics&) override;

    // Resized method: Handles layout updates
    void resized() override;

private:
    //==============================================================================
    // Utility methods

    // Applies the color palette to the UI elements
    void applyColorPalette();

    // Handles the login functionality
    void handleLogin();

    // Displays a custom alert message for login errors
    void showCustomAlert();

    //==============================================================================
    // Member variables

    // Logo image displayed on the UI
    juce::Image logoImage;

    // Text editor for username input
    juce::TextEditor userTextEditor;

    // Text editor for password input
    juce::TextEditor passwordTextEditor;

    // Button for initiating login
    juce::TextButton loginButton;

    // Label to display error messages
    juce::Label errorMessageLabel;

    // Rectangle area for positioning the logo
    juce::Rectangle<int> logoArea;

    // Prevents copying and ensures proper memory management
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
