#include "ofApp.h"


namespace VectorCalulatorMenuConstants
{
    constexpr ImVec2 MenuSize = ImVec2(500.f, 300.f);
}

namespace VectorDrawingConstants
{
    constexpr float CircleSize = 15.f;
    constexpr float CircleSizeSquared = 255.f;
    constexpr float LineThickness = 10.f;
}

void ofApp::setup()
{
	gui.setup(nullptr, false);
}

void ofApp::update()
{

}

void ofApp::draw()
{
    ofSetBackgroundColor(100, 100, 100);

    for (vpVector& vector : vectors)
    {
        vector.draw();
    }
    drawGui();
}

void ofApp::drawGui()
{
    gui.begin();
    ImGui::Begin("Vector Playground");
    ImGui::SetWindowSize(VectorCalulatorMenuConstants::MenuSize, ImGuiCond_Once);

    ImVec2 position = ImGui::GetWindowPos();
    ImVec2 size = ImGui::GetWindowSize();
    if (menuPosition.x != position.x || menuPosition.y != position.y)
    {
        menuPosition.set(position.x, position.y);
    }
    if (menuSize.x != size.x || menuSize.y != size.y)
    {
        menuSize.set(size.x, size.y);
    }

    ImGui::Columns(2);
    drawVectorList();
    ImGui::NextColumn();
    drawCalculator();
    ImGui::NextColumn();

    ImGui::End();

    gui.end();
    gui.draw();
}

void ofApp::drawVector(vpVector& vector)
{
    ImGui::ColorButton("", ofColorToImVec4(vector.color));
    ImGui::SameLine();
    ImGui::Text("[%d]", vector.id);
    ImGui::SameLine();
    ImGui::InputFloat2("", vector.length.getPtr());
}

void ofApp::drawVectorList()
{
    ImGui::BeginChild("VectorList");
    ImGui::Text("Vectors:");

    for (vpVector& vector : vectors)
    {
        static bool isSelected = false;
        ImGui::PushID(vector.id);
        if (ImGui::Selectable("", isSelected))
        {
            calculator.addVector(&vector);
        }
        ImGui::SameLine();
        drawVector(vector);
        ImGui::PopID();
    }

    ImGui::EndChild();
}

void ofApp::drawCalculator()
{
    // Input
    constexpr int kTextBufferSize = 512;
    constexpr char kOperationStrings[] = {'+', '-', 'X', '/'};
    char textBuffer[kTextBufferSize];
    std::string calculatorInputString = "";
    const std::vector<vpVector*>& inputs = calculator.GetInputs();
    const std::vector<vpOperation>& operations = calculator.GetOperations();
    if (inputs.size() != 0 && operations.size() != 0)
    {
        for (int index = 0; index < inputs.size(); index++)
        {
            calculatorInputString += "Vector " + std::to_string(inputs[index]->id) + " ";
            if (index < operations.size())
            {
                calculatorInputString += kOperationStrings[operations[index]];
            }
            calculatorInputString += "\n";
        }
    }
    strncpy(textBuffer, calculatorInputString.c_str(), kTextBufferSize);
    ImGui::PushID("CalculatorInput");
    ImGui::SetNextItemWidth(-1.f);
    ImGui::InputTextMultiline("", textBuffer, kTextBufferSize);
    ImGui::PopID();

    // Controls
    if (ImGui::Button("+"))
    {
        calculator.addOperation(vpOperation::Addition);
    }
    ImGui::SameLine();    
    if (ImGui::Button("-"))
    {
        calculator.addOperation(vpOperation::Subtraction);
    }
    ImGui::SameLine();
    if (ImGui::Button("X"))
    {
        calculator.addOperation(vpOperation::Multiplication);
    }
    ImGui::SameLine();    
    if (ImGui::Button("/"))
    {
        calculator.addOperation(vpOperation::Division);
    }
    if (ImGui::Button("=", ImVec2(-1.f, 0.f)))
    {
        calculator.calculate();
    }
}

bool ofApp::isClickingOnMenu(const ofVec2f& position)
{
    if ((position.x >= menuPosition.x && position.x <= menuPosition.x + menuSize.x)
        && (position.y >= menuPosition.y && position.y <= menuPosition.y + menuSize.y))
    {
        return true;
    }
    
    return false;
}

inline ImVec4 ofApp::ofColorToImVec4(const ofColor& color)
{
    return ImVec4(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
}

void ofApp::mouseDragged(int x, int y, int button)
{
    const ofVec2f mouseLocation = ofVec2f(x, y);

    if (isClickingOnMenu(mouseLocation))
    {
        return;
    }

    if (currentIndex != -1)
    {
        vectors[currentIndex].end.set(x, y);
        vectors[currentIndex].length = vectors[currentIndex].end - vectors[currentIndex].start;
    }
}

void ofApp::mousePressed(int x, int y, int button)
{
    constexpr int kInvalidIndex = -1;
    const ofVec2f mouseLocation = ofVec2f(x, y);

    // Don't create vector if we are actually clicking on the menu
    if (isClickingOnMenu(mouseLocation))
    {
        return;
    }

    // Check we didn't click an existing vector
    int existingVectorIndex = kInvalidIndex;
    bool bIsMatchingStartPoint = false;
    for (int index = 0; index < vectors.size(); index++)
    {
        const vpVector& vector = vectors[index];

        const ofVec2f differenceToStartPos = vector.start - mouseLocation;
        if (differenceToStartPos.lengthSquared() < VectorDrawingConstants::CircleSizeSquared)
        {
            existingVectorIndex = index;
            bIsMatchingStartPoint = true;
            break;
        }

        const ofVec2f differenceToEndPos = vector.end - mouseLocation;
        if (differenceToEndPos.lengthSquared() < VectorDrawingConstants::CircleSizeSquared)
        {
            existingVectorIndex = index;
            break;
        }
    }
    
    if (existingVectorIndex == kInvalidIndex)
    {
        // Add a new vector
        vectors.push_back(vpVector());
        currentIndex = vectors.size() - 1;
        vpVector& newVector = vectors[currentIndex];

        newVector.reset();
        newVector.start.set(x, y);
        newVector.color.set(ofRandom(50, 255), ofRandom(50, 255), ofRandom(50, 255));
        newVector.id = currentVectorId++;
    }
    else
    {
        // Reuse the existing one
        currentIndex = existingVectorIndex;
        vpVector& existingVector = vectors[currentIndex];

        // Swap around start and end locations as we only update the end location
        // when dragging the mouse.
        if (bIsMatchingStartPoint)
        {
            const ofVec2f startCopy = existingVector.start;
            existingVector.start = existingVector.end;
            existingVector.end = startCopy;
        }
    }
}

void ofApp::mouseReleased(int x, int y, int button)
{
    if (currentIndex != -1)
    {
        vpVector& currentVector = vectors[currentIndex];
        currentVector.length = currentVector.end - currentVector.start;
    }
}

void vpVector::draw()
{
    if (start == ofVec2f::zero() || end == ofVec2f::zero())
    {
        return;
    }

    ofSetColor(color);
    ofDrawCircle(start.x, start.y, 0.f, VectorDrawingConstants::CircleSize);
    ofDrawCircle(end.x, end.y, 0.f, VectorDrawingConstants::CircleSize);
    ofSetLineWidth(VectorDrawingConstants::LineThickness);
    ofLine(start.x, start.y, end.x, end.y);
}

void vpVector::reset()
{
    id = 0;
    start.set(ofVec2f::zero());
    end.set(ofVec2f::zero());
    color.set(255.f);
}

void vpCalculator::addVector(vpVector* input)
{
    if (pendingOperations.size() == pendingInputs.size())
    {
        pendingInputs.push_back(input);
    }
    else
    {
        // For every input we need an appropriate operation, replace the current input
        // if we don't have a new operation for it
        pendingInputs[pendingInputs.size() - 1] = input;
    }
}

void vpCalculator::addOperation(vpOperation operationType)
{
    if (pendingOperations.size() == pendingInputs.size())
    {
        // Replace the operation if we don't have an input for it yet
        pendingOperations[pendingOperations.size() - 1] = operationType;
    }
    else
    {
        pendingOperations.push_back(operationType);
    }
}

ofVec2f vpCalculator::calculate()
{
    if (pendingInputs.size() < 2)
    {
        return ofVec2f::zero();
    }

    ofVec2f result = pendingInputs[0]->length;
    for (int index = 1; index < pendingInputs.size(); index++)
    {
        if (index > pendingOperations.size() - 1)
        {
            break;
        }

        ofVec2f input = pendingInputs[index]->length;
        switch (pendingOperations[index])
        {
            case Addition:          result = result + input; break;
            case Subtraction:       result = result - input; break;
            case Multiplication:    result = result * input; break;
            case Division:          result = result / input; break;
        }
    }
    return result;
}

ofVec2f vpExpression::Solve()
{
    ofVec2f result = ofVec2f::zero();
    switch (operation)
    {
    case Addition:          result = a + b; break;
    case Subtraction:       result = a - b; break;
    case Multiplication:    result = a * b; break;
    case Division:          result = a / b; break;
    }
    return result;
}
