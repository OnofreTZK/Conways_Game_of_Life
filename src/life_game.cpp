#include "../include/life_game.h"

namespace life
{
//*NAMESPACE LIFE*//

LifeConfig::LifeConfig(Options origin_life)
{
  firstMan = origin_life;
  //Create cells table with borther, after now use for(1 to <= size()) to represent firstMan
  firstManCells.resize(firstMan.nLin + 2, std::vector<Cell>(firstMan.nCol+2));
  firstManChars.resize(firstMan.nLin, std::vector<char>(firstMan.nCol));

  //rendering alives
  for(int i = 0; i < firstMan.starter_config.size(); i++){
    for(int j = 0; j < firstMan.starter_config[0].size(); j++){
        if(firstMan.starter_config[i][j] == firstMan.aliveCell){
            firstManCells[i+1][j+1].Status = true;
        }
    }
  } 
  RenderNeighbours();
  RenderCharTable(firstManChars);
  printNeighboursTable();
}

void LifeConfig::RenderNeighbours(){
  for(int i = 1; i < firstManCells.size()-1; i++){
    for(int j = 1; j < firstManCells[i].size()-1; j++){
      
      //reset neighbours
      firstManCells[i][j].neighbours = 0;

      
        if(firstManCells[i-1][j].Status == true){
          firstManCells[i][j].neighbours++;
        }
        if(firstManCells[i+1][j].Status == true){
          firstManCells[i][j].neighbours++;
        }
        if(firstManCells[i][j-1].Status == true){
          firstManCells[i][j].neighbours++;
        }
        if(firstManCells[i][j+1].Status == true){
          firstManCells[i][j].neighbours++;
        }
        if(firstManCells[i-1][j-1].Status == true){
          firstManCells[i][j].neighbours++;
        }
        if(firstManCells[i+1][j-1].Status == true){
          firstManCells[i][j].neighbours++;
        }
        if(firstManCells[i+1][j+1].Status == true){
          firstManCells[i][j].neighbours++;
        }
        if(firstManCells[i-1][j+1].Status == true){
          firstManCells[i][j].neighbours++;
        }
      
    }
  }
}

void LifeConfig::RefreshGeneration(){
  for(int i = 1; i < firstManCells.size()-1; i++){
    for(int j = 1; j < firstManCells[i].size()-1; j++){
      //Rule 1
      if (firstManCells[i][j].Status == true and firstManCells[i][j].neighbours <= 1){
        firstManCells[i][j].Status == false;
      }
      //Rule 2
      else if (firstManCells[i][j].Status == true and firstManCells[i][j].neighbours >= 4){
        firstManCells[i][j].Status == false;
      }
      //Rule 3
      else if (firstManCells[i][j].Status == true and firstManCells[i][j].neighbours == 2 or firstManCells[i][j].neighbours == 3){
        firstManCells[i][j].Status == true;
      }
      //Rule 4
      else if (firstManCells[i][j].Status == false and firstManCells[i][j].neighbours == 3){
        firstManCells[i][j].Status == true;
      }
    }
  }
  RenderNeighbours();
  RenderCharTable(firstManChars);
}

void LifeConfig::RenderCharTable(std::vector<std::vector<char>> &myCharVector){
  for(int i = 0; i < myCharVector.size(); i++){
    for(int j = 0; j < myCharVector[i].size(); j++){
      if(firstManCells[i+1][j+1].Status == true){
        myCharVector[i][j] = firstMan.aliveCell;
      }else{
        myCharVector[i][j] = '-';
      }
    }
  }  
}

void LifeConfig::PrintTable()
{
  std::cout << "Lines: " << firstMan.nLin << std::endl;
  std::cout << "Cols: " << firstMan.nCol << std::endl;
  std::cout << "\n\n";

  for( int i = 0; i < firstMan.nLin; i++ )
  {
      std::cout << "[";

      for( int j = 0; j < firstMan.nCol; j++ )
      {
          if( firstManChars[i][j] != firstMan.aliveCell )
          {
              std::cout << "-";
          }
          else
              std::cout << firstManChars[i][j];
      }
      std::cout << "]" << std::endl;
  }
}

void LifeConfig::printNeighboursTable(){
  for(int i = 1; i < firstManCells.size()-1; i++){
    for(int j = 1; j < firstManCells[i].size()-1; j++){
      std::cout << firstManCells[i][j].neighbours << " ";
    }
    std::cout << std::endl;
  }
}


//*END NAMESPACE LIFE*//
} // namespace life