//------- Includes -------
#include "MainComponent.h"
#include "HomeComponent.h"
#include <iostream>
#include "Model.h"

//------- Constructor -------
// Initializes the MainComponent and sets up its UI elements
MainComponent::MainComponent()
{
    // Set the initial size of the component
    setSize(600, 400);

    // Load the logo image from the specified path
    logoImage = juce::ImageFileFormat::loadFrom(
        juce::File::getCurrentWorkingDirectory().getChildFile("/Users/user/JUCE-PROJECTS/MVCpp-ThroughTheLookingGlass/Source/emsi-true.png"));
    
    juce::Logger::writeToLog("Working directory: " + juce::File::getCurrentWorkingDirectory().getFullPathName());

    // Apply a custom color palette to the UI
    applyColorPalette();

    // Set up the username text editor
    addAndMakeVisible(userTextEditor);
    userTextEditor.setFont(juce::FontOptions().withHeight(16.0f));
    userTextEditor.setTextToShowWhenEmpty("User", juce::Colours::grey);
    userTextEditor.setJustification(juce::Justification::centredLeft);
    userTextEditor.setInputRestrictions(12);
    //resize the text editor container
    
    // Set up the password text editor
    addAndMakeVisible(passwordTextEditor);
    passwordTextEditor.setFont(juce::FontOptions().withHeight(16.0f));
    passwordTextEditor.setTextToShowWhenEmpty("Password", juce::Colours::grey);
    passwordTextEditor.setJustification(juce::Justification::centredLeft);
    passwordTextEditor.setPasswordCharacter('*');
    passwordTextEditor.setInputRestrictions(12);
    // Set up the login button
    addAndMakeVisible(loginButton);
    loginButton.setButtonText("Login");

    // Set up the error message label
    addAndMakeVisible(errorMessageLabel);

    // Attach a callback to the login button
    loginButton.onClick = [this]() {
        handleLogin();
    };

    // Initially hide the error message label
    errorMessageLabel.setVisible(false);
}

//------- Destructor -------
// Cleans up the MainComponent
MainComponent::~MainComponent() {}

//------- Apply Color Palette -------
// Configures the color scheme for various UI elements
void MainComponent::applyColorPalette()
{
    setColour(juce::ResizableWindow::backgroundColourId, juce::Colours::whitesmoke);

    userTextEditor.setColour(juce::TextEditor::backgroundColourId, juce::Colours::white);
    userTextEditor.setColour(juce::TextEditor::textColourId, juce::Colours::darkgreen);

    passwordTextEditor.setColour(juce::TextEditor::backgroundColourId, juce::Colours::white);
    passwordTextEditor.setColour(juce::TextEditor::textColourId, juce::Colours::darkgreen);

    loginButton.setColour(juce::TextButton::buttonColourId, juce::Colours::mediumseagreen);
    loginButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    loginButton.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    loginButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);

    // Styling for the error message label
    errorMessageLabel.setFont(juce::FontOptions(16.0f, juce::Font::bold));
    errorMessageLabel.setColour(juce::Label::textColourId, juce::Colours::red);
    errorMessageLabel.setJustificationType(juce::Justification::centred);
}

//------- Paint Method -------
// Customizes the component's appearance
void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(findColour(juce::ResizableWindow::backgroundColourId));

    if (logoImage.isValid())
    {
        g.drawImageWithin(logoImage, logoArea.getX(), logoArea.getY(),
                          logoArea.getWidth(), logoArea.getHeight(),
                          juce::RectanglePlacement::centred | juce::RectanglePlacement::onlyReduceInSize);
    }
    else
    {
        g.setColour(juce::Colours::darkgreen);
        g.fillRect(logoArea);
        g.setColour(juce::Colours::green);
        g.drawRect(logoArea, 2);
        g.setFont(16.0f);
        g.setColour(juce::Colours::white);
        g.drawText("Logo", logoArea, juce::Justification::centred, true);
    }
}

//------- Resized Method -------
// Handles layout and positioning of components
void MainComponent::resized()
{
    auto area = getLocalBounds().reduced(20);

    logoArea = area.removeFromTop(100);

    auto formArea = area.removeFromTop(120);
    userTextEditor.setBounds(formArea.removeFromTop(40).reduced(10));
    passwordTextEditor.setBounds(formArea.removeFromTop(40).reduced(10));

    loginButton.setBounds(area.removeFromTop(40).reduced(100, 0));

    // Position the error message label below the login button
    errorMessageLabel.setBounds(area.removeFromTop(40).reduced(100, 0));
}

//------- Handle Login -------
// Processes login functionality
void MainComponent::handleLogin()
{
    // Get the username and password from the text fields
    auto username = userTextEditor.getText().toStdString();
    auto password = passwordTextEditor.getText().toStdString();

    // Disable the login button to prevent multiple clicks
    loginButton.setEnabled(false);

    // Create a Model object to interact with the database
    Model model("/Users/user/JUCE-PROJECTS/MVCpp-ThroughTheLookingGlass/Source/cpp_mvc.sqlite");

    // Check if the credentials match the database records
    bool loginSuccessful = model.checkLoginCredentials(username, password);

    // Re-enable the login button
    loginButton.setEnabled(true);

    if (loginSuccessful)
    {
        juce::Logger::writeToLog("Login successful! Redirecting to HomeComponent...");

        // Hide error message on success
        errorMessageLabel.setVisible(false);

        // Transition to the HomeComponent
        auto* homeComponent = new HomeComponent();
        auto* window = dynamic_cast<juce::ResizableWindow*>(getParentComponent());
        if (window != nullptr)
        {
            window->setContentOwned(homeComponent, true);
        }

        juce::Logger::writeToLog("Switched to HomeComponent");
    }
    else
    {
        showCustomAlert(); // Show error if login fails
    }
}

//------- Show Custom Alert -------
// Displays an error message when login fails
void MainComponent::showCustomAlert()
{
    errorMessageLabel.setText("Invalid username or password.", juce::dontSendNotification);
    errorMessageLabel.setVisible(true);
}
