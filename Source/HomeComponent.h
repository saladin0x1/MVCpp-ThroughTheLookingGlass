//------- Include Guards -------
#pragma once

//------- Includes -------
#include <JuceHeader.h>
#include "Model.h"
#include "MainComponent.h"

//==============================================================================
/*
    HomeComponent is responsible for displaying user information and related UI elements.
*/
class HomeComponent : public juce::Component
{
public:
    //==============================================================================
    // Constructor
    HomeComponent();

    // Destructor
    ~HomeComponent() override;

    //==============================================================================
    // JUCE Methods

    // Paint method: Handles custom drawing of the component
    void paint(juce::Graphics&) override;

    // Resized method: Handles layout and positioning of subcomponents
    void resized() override;

    //==============================================================================
    // Custom Methods

    // Displays a custom alert message for errors or notifications
    void showCustomAlert(const juce::String& message);

    // Displays user information on the UI
    void showUserInfo();
    // Function to handle "Back to Main" button click
    void goBackToMain();  // Ensure this function is declared to be called in HomeComponent
private:
    //==============================================================================
    // UI Components

    // Labels for displaying student information
    juce::Label nameLabel;        // Displays the student's name
    juce::Label lastNameLabel;    // Displays the student's last name
    juce::Label idLabel;          // Displays the student's ID
    juce::Label classLabel;       // Displays the student's class
    juce::Label errorMessageLabel; // Displays error messages (styled and positioned)

    // Image component for displaying the student's profile picture
    juce::ImageComponent studentImageComponent;

    // Button to trigger the display of user information
    juce::TextButton showUserInfoButton, backButton;  // Declare backButton here

    //==============================================================================
    // Data Model

    // Model instance for accessing database or user-related information
    Model model;

    //==============================================================================
    // Prevents copying and ensures proper memory management
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HomeComponent)
};
