#include "HomeComponent.h"
#include "MainComponent.h"
// Constructor: Initializes the HomeComponent
HomeComponent::HomeComponent() : model("/Users/user/JUCE-PROJECTS/MVCpp-ThroughTheLookingGlass/Source/cpp_mvc.sqlite")
{
    setSize(600, 400);  // Set the initial size of the component

    // Set up labels
    juce::Font labelFont(juce::FontOptions().withHeight(16.0f));
    for (auto* label : { &nameLabel, &lastNameLabel, &idLabel, &classLabel }) {
        label->setFont(labelFont);
        label->setColour(juce::Label::textColourId, juce::Colours::darkgreen);
        addAndMakeVisible(label);
    }

    // Initialize and style the error message label
    errorMessageLabel.setFont(juce::FontOptions(16.0f, juce::Font::bold));
    errorMessageLabel.setColour(juce::Label::textColourId, juce::Colours::red);
    errorMessageLabel.setJustificationType(juce::Justification::centred);
    errorMessageLabel.setVisible(false); // Initially hidden
    addAndMakeVisible(errorMessageLabel);

    // Set up the show user info button
    showUserInfoButton.setButtonText("Show User Info");
    showUserInfoButton.onClick = [this] { showUserInfo(); };
    addAndMakeVisible(showUserInfoButton);

    // Set up the back button to return to MainComponent
    backButton.setButtonText(" <- Back");  // Add an arrow symbol for visual clarity
    backButton.onClick = [this] { goBackToMain(); };  // When clicked, it will call goBackToMain()
    addAndMakeVisible(backButton);

    // Load student data (example userId = 1 for demo purposes)
    std::string name, lastName, id, className;
    try {
        model.loadStudentData(1, name, lastName, id, className);  // Load data for userId = 1

        // Update labels with fetched data
        nameLabel.setText("Name: " + name, juce::dontSendNotification);
        lastNameLabel.setText("Last Name: " + lastName, juce::dontSendNotification);
        idLabel.setText("ID: " + id, juce::dontSendNotification);
        classLabel.setText("Class: " + className, juce::dontSendNotification);

    } catch (const std::exception& e) {
        showCustomAlert("Error: Failed to load student data.");
    }
}

// Destructor
HomeComponent::~HomeComponent() {}

// Paint method: Handles custom drawing
void HomeComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::whitesmoke);

    // Draw a background grid
    g.setColour(juce::Colours::darkgrey);
    g.setOpacity(0.1f);
    int gridSpacing = 20;
    for (int x = 0; x < getWidth(); x += gridSpacing) {
        for (int y = 0; y < getHeight(); y += gridSpacing) {
            g.fillEllipse(x, y, 2, 2);
        }
    }

    // Draw student image area (empty for now)
    g.setColour(juce::Colours::red);
    juce::Rectangle<int> imageArea(getWidth() - 160, 40, 140, 140);
    g.drawRect(imageArea, 3);

    g.setColour(juce::Colours::white);
    g.setFont(juce::FontOptions(14.0f));
    g.drawText("Student Image", imageArea.reduced(5), juce::Justification::centred);

    // Draw the border around the component
    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);
}

// Resized method: Handles layout and positioning of subcomponents
void HomeComponent::resized()
{
    auto bounds = getLocalBounds().reduced(20);

    // Set bounds for the back button (at the top-left of the component)
    backButton.setBounds(bounds.removeFromTop(40).removeFromLeft(100));  // Adjust as necessary

    // Set bounds for labels (left side of the component)
    int labelWidth = bounds.getWidth() / 2;
    nameLabel.setBounds(bounds.removeFromTop(40).removeFromLeft(labelWidth));
    lastNameLabel.setBounds(bounds.removeFromTop(40).removeFromLeft(labelWidth));
    idLabel.setBounds(bounds.removeFromTop(40).removeFromLeft(labelWidth));
    classLabel.setBounds(bounds.removeFromTop(40).removeFromLeft(labelWidth));

    // Set the position for the show user info button (below the labels)
    showUserInfoButton.setBounds(bounds.removeFromTop(40).removeFromLeft(labelWidth));

    // Set position for the error message label (below the button)
    errorMessageLabel.setBounds(bounds.removeFromTop(40).removeFromLeft(labelWidth));
}

// goBackToMain function: Handles navigation to the MainComponent
void HomeComponent::goBackToMain()
{
    // Avoid memory leak by using unique_ptr for MainComponent
    
    auto* mainComp = new MainComponent();
    auto* window = dynamic_cast<juce::ResizableWindow*>(getParentComponent());
    if (window != nullptr)
    {
        window->setContentOwned(mainComp, true);
    }

    juce::Logger::writeToLog("Switched Back to Component");
}

// Function to display user info when clicked
void HomeComponent::showUserInfo()
{
    // Update labels with user info when the button is clicked
    std::string name, lastName, id, className;
    try {
        model.loadStudentData(12354, name, lastName, id, className);  // Load data for userId = 12354

        // Update labels with fetched data
        nameLabel.setText("Name: " + name, juce::dontSendNotification);
        lastNameLabel.setText("Last Name: " + lastName, juce::dontSendNotification);
        idLabel.setText("ID: " + id, juce::dontSendNotification);
        classLabel.setText("Class: " + className, juce::dontSendNotification);

        errorMessageLabel.setVisible(false); // Hide any error messages on success

    } catch (const std::exception& e) {
        showCustomAlert("Error: Failed to load user information.");
    }
}

// Function to show custom alert messages
void HomeComponent::showCustomAlert(const juce::String& message)
{
    errorMessageLabel.setText(message, juce::dontSendNotification);
    errorMessageLabel.setVisible(true); // Show the error message label
}
