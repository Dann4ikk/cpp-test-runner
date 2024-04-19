#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <chrono>

namespace fs = std::filesystem;

const std::string RESET_COLOR = "\033[0m";
const std::string GREEN = "\033[32m";
const std::string RED = "\033[31m";
const std::string YELLOW = "\033[33m";

bool runTest(const std::string &parentDir, const std::string &testDir, int testNum, bool showInput)
{
  // check if the first test has leading zero numerotation, therfore check if every test has leading zero numerotation
  bool isNumerotationWithLeadingZeros = fs::exists(testDir + "/input.0" + std::to_string(1));

  std::string inputFileName = testDir + "/input." + std::to_string(testNum);
  std::string outputFileName = testDir + "/output." + std::to_string(testNum);

  // Add leading zeros for tests between 1 and 9
  if (testNum < 10 && isNumerotationWithLeadingZeros)
  {
    inputFileName = testDir + "/input.0" + std::to_string(testNum);
    outputFileName = testDir + "/output.0" + std::to_string(testNum);
  }

  // Prepare input file
  std::ifstream inputFile(inputFileName);
  std::ifstream outputFile(parentDir + "/output.txt");

  std::ofstream inputCopy(parentDir + "/input.txt");
  inputCopy << inputFile.rdbuf();
  inputCopy.close();
  inputFile.close();

  auto startTime = std::chrono::high_resolution_clock::now();

  // Run the program
  system((parentDir + "/main").c_str());

  auto endTime = std::chrono::high_resolution_clock::now();
  auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

  // Check output
  std::ifstream expectedOutput(outputFileName);
  std::string actualOutput((std::istreambuf_iterator<char>(outputFile)),
                           std::istreambuf_iterator<char>());

  std::string expectedOutputStr((std::istreambuf_iterator<char>(expectedOutput)),
                                std::istreambuf_iterator<char>());

  std::ifstream inputCopyIn(parentDir + "/input.txt");
  std::string inputStr((std::istreambuf_iterator<char>(inputCopyIn)),
                       std::istreambuf_iterator<char>());
  inputCopyIn.close();

  std::string normalizedActualOutput, normalizedExpectedOutput, normalizedInput;
  for (char c : actualOutput)
  {
    if (c == '\r')
    {
      continue; // Skip carriage returns
    }
    else if (c == '\n')
    {
      normalizedActualOutput += '\n';
    }
    else
    {
      normalizedActualOutput += c;
    }
  }
  for (char c : expectedOutputStr)
  {
    if (c == '\r')
    {
      continue; // Skip carriage returns
    }
    else if (c == '\n')
    {
      normalizedExpectedOutput += '\n';
    }
    else
    {
      normalizedExpectedOutput += c;
    }
  }
  for (char c : inputStr)
  {
    if (c == '\r')
    {
      continue; // Skip carriage returns
    }
    else if (c == '\n')
    {
      normalizedInput += '\n';
    }
    else
    {
      normalizedInput += c;
    }
  }

  // Trim leading and trailing whitespace from normalized outputs
  normalizedActualOutput.erase(0, normalizedActualOutput.find_first_not_of(" \n\r\t"));
  normalizedActualOutput.erase(normalizedActualOutput.find_last_not_of(" \n\r\t") + 1);
  normalizedExpectedOutput.erase(0, normalizedExpectedOutput.find_first_not_of(" \n\r\t"));
  normalizedExpectedOutput.erase(normalizedExpectedOutput.find_last_not_of(" \n\r\t") + 1);
  normalizedInput.erase(0, normalizedInput.find_first_not_of(" \n\r\t"));
  normalizedInput.erase(normalizedInput.find_last_not_of(" \n\r\t") + 1);

  std::cout << "\n"
            << YELLOW << "===== Test " << std::setw(2) << std::setfill('0') << testNum << " =====" << RESET_COLOR << "\n\n";
  if (showInput)
  {
    std::cout << "Input:\n"
              << inputStr << "\n\n";
  }
  std::cout << "Actual Output:\n"
            << normalizedActualOutput << "\n\n";
  std::cout << "Expected Output:\n"
            << normalizedExpectedOutput << "\n\n";
  std::cout << "Time Taken: " << elapsedTime << " ms\n";

  outputFile.close();
  expectedOutput.close();

  if (normalizedActualOutput == normalizedExpectedOutput)
  {
    std::cout << GREEN << "Test " << std::setw(2) << std::setfill('0') << testNum << " passed." << RESET_COLOR << "\n";
    return true;
  }
  else
  {
    std::cout << RED << "Test " << std::setw(2) << std::setfill('0') << testNum << " failed." << RESET_COLOR << "\n";
    return false;
  }
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " <parent_directory> [-s|--show-input]\n";
    return 1;
  }

  std::string parentDir(argv[1]);
  std::string testDir = parentDir + "/tests";
  int numPassed = 0;
  int testNum = 1;
  bool showInput = false;

  for (int i = 2; i < argc; ++i)
  {
    std::string arg(argv[i]);
    if (arg == "-s" || arg == "--show-input")
    {
      showInput = true;
    }
  }

  // Compile the main.cpp file
  system(("g++ " + parentDir + "/main.cpp -o " + parentDir + "/main").c_str());

  while (true)
  {

    // check if the first test has leading zero numerotation, therfore check if every test has leading zero numerotation
    bool isNumerotationWithLeadingZeros = fs::exists(testDir + "/input.0" + std::to_string(1));

    std::string inputFileName = testDir + "/input." + std::to_string(testNum);
    std::string outputFileName = testDir + "/output." + std::to_string(testNum);

    // Add leading zeros for tests between 1 and 9
    if (testNum < 10 && isNumerotationWithLeadingZeros)
    {
      inputFileName = testDir + "/input.0" + std::to_string(testNum);
      outputFileName = testDir + "/output.0" + std::to_string(testNum);
    }

    if (!fs::exists(inputFileName) || !fs::exists(outputFileName))
    {
      break;
    }

    if (runTest(parentDir, testDir, testNum, showInput))
    {
      numPassed++;
    }

    testNum++;
  }

  std::cout << "\n"
            << YELLOW << "===== Summary =====" << RESET_COLOR << "\n";
  std::cout << numPassed << "/" << testNum - 1 << " tests passed.\n";

  return 0;
}
