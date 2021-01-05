#include "Algorithm.h"
#include "Input.h"
#include "StringUtil.h"

using namespace StringUtil;
using namespace Algorithm;

struct Matrix;

vector<Matrix>                  matrices;
unordered_map<int, vector<int>> graph;
unordered_map<int, Matrix>      tileIdMatrixMap;

struct Matrix
{
  vector<string>         mData;
  vector<vector<string>> mUniqueBorders;
  int                    mTileId{ 0 };

  string & operator[](int i) { return mData[i]; }

  int GetSize() const { return mData.size(); }

  void AddRow(const string & aRow) { mData.push_back(aRow); }

  //---------------------------------------------------------------

  string GetLeftBorder()
  {
    string leftColumn;
    for (int i = 0; i < mData.size(); i++)
      leftColumn += mData[i][0];

    return leftColumn;
  }

  string GetRightBorder()
  {
    string rightColumn;
    for (int i = 0; i < mData.size(); i++)
      rightColumn += mData[i][mData.size() - 1];

    return rightColumn;
  }

  string GetTopBorder() { return mData[0]; }

  string GetBottomBorder() { return mData[mData.size() - 1]; }

  //---------------------------------------------------------------

  string GetReverseLeftBorder()
  {
    string leftBorder = GetLeftBorder();

    return { rbegin(leftBorder), rend(leftBorder) };
  }

  string GetReverseRightBorder()
  {
    string rightBorder = GetRightBorder();

    return { rbegin(rightBorder), rend(rightBorder) };
  }

  string GetReverseTopBorder()
  {
    string topBorder = GetTopBorder();

    return { rbegin(topBorder), rend(topBorder) };
  }

  string GetReverseBottomBorder()
  {
    string bottomBorder = GetBottomBorder();

    return { rbegin(bottomBorder), rend(bottomBorder) };
  }

  //---------------------------------------------------------------

  vector<string> GetAllBorders()
  {
    return { GetTopBorder(),  GetReverseTopBorder(),  GetBottomBorder(), GetReverseBottomBorder(),
             GetLeftBorder(), GetReverseLeftBorder(), GetRightBorder(),  GetReverseRightBorder() };
  }

  vector<vector<string>> GetPairedBorders()
  {
    return { { GetTopBorder(), GetReverseTopBorder() },
             { GetBottomBorder(), GetReverseBottomBorder() },
             { GetLeftBorder(), GetReverseLeftBorder() },
             { GetRightBorder(), GetReverseRightBorder() } };
  }

  bool ContainsBorder(const vector<string> & aPairedBorders)
  {
    auto allBorders = GetAllBorders();

    return Contains(allBorders, aPairedBorders[0]) || Contains(allBorders, aPairedBorders[1]);
  }

  //---------------------------------------------------------------

  void Rotate()
  {
    vector<string> newData = mData;

    for (int i = 0; i < mData.size(); i++)
    {
      for (int j = 0; j < mData.size(); j++)
      {
        newData[j][mData.size() - 1 - i] = mData[i][j];
      }
    }

    mData = newData;
  }

  void Flip()
  {
    vector<string> newData;

    for (auto & row : mData)
    {
      newData.push_back({ rbegin(row), rend(row) });
    }

    mData = newData;
  }

  vector<Matrix> GetAllTransforms()
  {
    vector<Matrix> allTransforms;

    // original state
    allTransforms.push_back(*this);

    Rotate();

    // rotated 90 degrees
    allTransforms.push_back(*this);

    Rotate();

    // rotated 180 degrees
    allTransforms.push_back(*this);

    Rotate();

    // rotated 270 degrees
    allTransforms.push_back(*this);

    // revert to original rotation
    Rotate();

    Flip();

    // flipped
    allTransforms.push_back(*this);

    Rotate();

    // flipped and rotated 90 degrees
    allTransforms.push_back(*this);

    Rotate();

    // flipped and rotated 180 degrees
    allTransforms.push_back(*this);

    Rotate();

    // flipped and rotated 270 degrees
    allTransforms.push_back(*this);

    // revert to original state
    Rotate();
    Flip();

    return allTransforms;
  }

  //---------------------------------------------------------------

  void RemoveBorders()
  {
    mData.erase(mData.begin());
    mData.pop_back();

    for (auto & row : mData)
    {
      row.erase(row.begin());
      row.pop_back();
    }
  }

  void Print()
  {
    for (int i = 0; i < mData.size(); i++)
    {
      for (int j = 0; j < mData[i].size(); j++)
        cout << mData[i][j];

      cout << endl;
    }

    cout << endl;
  }
};

int GetUniqueBorderCount(Matrix & aMatrix)
{
  int count = 0;

  for (auto & pairedBorders : aMatrix.GetPairedBorders())
  {
    bool isUnique = true;

    for (auto & matrix : matrices)
    {
      if (matrix.mTileId == aMatrix.mTileId)
        continue;

      if (matrix.ContainsBorder(pairedBorders))
      {
        graph[aMatrix.mTileId].push_back(matrix.mTileId);
        isUnique = false;
      }
    }

    if (isUnique)
    {
      count++;
      aMatrix.mUniqueBorders.push_back(pairedBorders);
    }
  }

  return count;
}

pair<int, int> GetOrderedTilesPos(int aIndex, int aSize)
{
  return make_pair(aIndex / aSize, aIndex % aSize);
}

int GetAdjacentNodesCount(int aPosX, int aPosY, int aSize)
{
  if (aPosX == 0 || aPosX == aSize - 1)
  {
    // corners
    if (aPosY == 0 || aPosY == aSize - 1)
      return 2;

    // edges
    return 3;
  }
  else
  {
    // edges
    if (aPosY == 0 || aPosY == aSize - 1)
      return 3;

    return 4;
  }
}

bool IsPlacedTile(const vector<vector<int>> & aOrderedTiles, int aTileId)
{
  for (int i = 0; i < aOrderedTiles.size(); i++)
  {
    for (int j = 0; j < aOrderedTiles[i].size(); j++)
    {
      if (aOrderedTiles[i][j] == aTileId)
        return true;
    }
  }

  return false;
}

void Solution(bool aPartTwo);
void PartOne();
void PartTwo();

int main()
{
  PartTwo();

  return 0;
}

void Solution(bool aPartTwo)
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto lines = reader.ReadStrings();

  Matrix currentMatrix;
  int    tileId = 0;

  for (const auto & line : lines)
  {
    if (line.substr(0, 4) == "Tile")
    {
      auto tokens = TokenizeString(line);
      tokens[1].pop_back();
      tileId = stoi(tokens[1]);
    }
    else if (line.empty())
    {
      currentMatrix.mTileId = tileId;
      matrices.push_back(currentMatrix);
      currentMatrix = {};
    }
    else
    {
      currentMatrix.AddRow(line);
    }
  }

  vector<int> cornerTileIds;

  for (auto & matrix : matrices)
  {
    if (GetUniqueBorderCount(matrix) == 2)
    {
      cornerTileIds.push_back(matrix.mTileId);
    }
  }

  if (!aPartTwo)
  {
    long long product = 1;
    for (auto tileId : cornerTileIds)
      product *= tileId;

    cout << product;

    return;
  }

  for (auto & matrix : matrices)
  {
    tileIdMatrixMap[matrix.mTileId] = matrix;
  }

  int orderedTilesSize = sqrt(matrices.size());

  vector<vector<int>> orderedTiles(orderedTilesSize, vector<int>(orderedTilesSize, 0));

  // corners: 3607, 1697, 2731, 1399

  int currentNodeId = 3607;
  int currentIndex  = 0;

  orderedTiles[0][0] = currentNodeId;

  auto & initialTile = tileIdMatrixMap[currentNodeId];
  assert(initialTile.mUniqueBorders.size() == 2);

  auto initialTransforms = initialTile.GetAllTransforms();

  for (auto & transform : initialTransforms)
  {
    if (Contains(initialTile.mUniqueBorders[0], transform.GetLeftBorder()) &&
        Contains(initialTile.mUniqueBorders[1], transform.GetTopBorder()))
    {
      initialTile = transform;
      break;
    }

    if (Contains(initialTile.mUniqueBorders[0], transform.GetTopBorder()) &&
        Contains(initialTile.mUniqueBorders[1], transform.GetLeftBorder()))
    {
      initialTile = transform;
      break;
    }
  }

  while (true)
  {
    int previousRow = 0;

    if (currentIndex != 0)
    {
      auto position = GetOrderedTilesPos(currentIndex, orderedTilesSize);

      orderedTiles[position.first][position.second] = currentNodeId;

      previousRow = position.first;
    }

    currentIndex++;
    if (currentIndex == orderedTilesSize * orderedTilesSize)
      break;

    auto nextPosition = GetOrderedTilesPos(currentIndex, orderedTilesSize);

    if (nextPosition.first == previousRow + 1)
    {
      currentNodeId = orderedTiles[previousRow][0];
    }

    auto & adjacentNodes = graph[currentNodeId];

    int adjacentNodesCount =
      GetAdjacentNodesCount(nextPosition.first, nextPosition.second, orderedTilesSize);

    vector<int> adjacentNodesCandidates;
    for (int adjacentNode : adjacentNodes)
    {
      if (IsPlacedTile(orderedTiles, adjacentNode))
        continue;

      if (graph[adjacentNode].size() == adjacentNodesCount)
        adjacentNodesCandidates.push_back(adjacentNode);
    }

    bool foundCandidate = false;

    for (int candidate : adjacentNodesCandidates)
    {
      auto & candidateTile = tileIdMatrixMap[candidate];
      auto   transforms    = candidateTile.GetAllTransforms();

      for (auto & transform : transforms)
      {
        bool foundY = false, foundX = false;

        // check bottom with top
        if (nextPosition.first >= 1)
        {
          auto & topTile =
            tileIdMatrixMap[orderedTiles[nextPosition.first - 1][nextPosition.second]];
          foundY = (topTile.GetBottomBorder() == transform.GetTopBorder());
        }

        // check right with left
        if (nextPosition.second >= 1)
        {
          auto & leftTile =
            tileIdMatrixMap[orderedTiles[nextPosition.first][nextPosition.second - 1]];
          foundX = (leftTile.GetRightBorder() == transform.GetLeftBorder());
        }

        if ((nextPosition.first >= 1) && (nextPosition.second >= 1))
        {
          if (foundY && foundX)
          {
            foundCandidate = true;
            candidateTile  = transform;
            break;
          }
        }
        else if (nextPosition.first >= 1 && foundY)
        {
          foundCandidate = true;
          candidateTile  = transform;
          break;
        }
        else if (nextPosition.second >= 1 && foundX)
        {
          foundCandidate = true;
          candidateTile  = transform;
          break;
        }
      }

      if (foundCandidate)
      {
        currentNodeId = candidate;
        break;
      }
    }

    assert(foundCandidate);
  }

  vector<vector<Matrix>> tilesWithoutBorders;

  for (int i = 0; i < orderedTilesSize; i++)
  {
    vector<Matrix> tilesRow;

    for (int j = 0; j < orderedTilesSize; j++)
    {
      auto & tile = tileIdMatrixMap[orderedTiles[i][j]];
      tile.RemoveBorders();

      tilesRow.push_back(tile);
    }

    tilesWithoutBorders.push_back(tilesRow);
  }

  Matrix finalMap;
  int    sizeWithoutBorders = tileIdMatrixMap[orderedTiles[0][0]].GetSize();

  for (int i = 0; i < orderedTilesSize * sizeWithoutBorders; i++)
  {
    string row;

    for (int j = 0; j < orderedTilesSize * sizeWithoutBorders; j++)
    {
      Matrix & currentMatrix = tilesWithoutBorders[i / sizeWithoutBorders][j / sizeWithoutBorders];

      row += currentMatrix[i % sizeWithoutBorders][j % sizeWithoutBorders];
    }

    finalMap.AddRow(row);
  }

  // sea monster
  //                  #
  //#    ##    ##    ###
  // #  #  #  #  #  #

  vector<pair<int, int>> seaMonster{ { 0, 18 }, { 1, 0 },  { 1, 5 },  { 1, 6 },  { 1, 11 },
                                     { 1, 12 }, { 1, 17 }, { 1, 18 }, { 1, 19 }, { 2, 1 },
                                     { 2, 4 },  { 2, 7 },  { 2, 10 }, { 2, 13 }, { 2, 16 } };

  auto allTransforms = finalMap.GetAllTransforms();
  int  monsterCount  = 0;

  for (auto & transform : allTransforms)
  {
    for (int i = 0; i < transform.GetSize() - 3; i++)
    {
      for (int j = 0; j < transform.GetSize() - 20; j++)
      {
        int sum = 0;
        for (auto & [k, l] : seaMonster)
        {
          if (transform[i + k][j + l] == '#')
            sum++;
        }

        if (sum == seaMonster.size())
          monsterCount++;
      }
    }

    if (monsterCount > 0)
    {
      transform.Print();
      break;
    }
  }

  int count = 0;

  for (int i = 0; i < finalMap.GetSize(); i++)
  {
    for (int j = 0; j < finalMap.GetSize(); j++)
    {
      if (finalMap[i][j] == '#')
        count++;
    }
  }

  cout << count - monsterCount * seaMonster.size() << endl;
}

void PartOne()
{
  Solution(false);
}

void PartTwo()
{
  Solution(true);
}
