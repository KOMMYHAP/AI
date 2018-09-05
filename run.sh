export srcDir=$HOME/programs/AI && export destDir=$HOME/miniaicups/madcars/Runners && g++ -std=c++17 *.cpp -o main && python3 $destDir/localrunner.py -f "$srcDir/main"
