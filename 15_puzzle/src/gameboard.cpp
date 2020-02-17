#include "gameboard.h"
#include <algorithm>
#include <random>
#include <QDebug>

namespace  {
    bool isAdjacent(const GameBoard::Position f, const GameBoard::Position s)
    {
        if (f == s)
            return false;

        const auto calcDistance = [](const size_t pos1, size_t pos2) {
            int distance = static_cast<int>(pos1);
            distance -= static_cast<int>(pos2);
            distance = std::abs(distance);
            return distance;
        };
        bool result {false};
        if(f.first == s.first) {
            int distance = calcDistance(f.second, s.second);
            if (distance == 1)
                result = true;
        } else  if (f.second == s.second) {
            int distance = calcDistance(f.first, s.first);
            if(distance == 1) {
                result = true;
            }
        }

        return result;
    }
}

GameBoard::GameBoard(const size_t boardDimension,
                     QObject* parent)
    : QAbstractListModel{parent},
      m_dimension{boardDimension},
    m_boardSize {m_dimension * m_dimension},
    m_stepCount {0}
{

    m_rawBoard.resize(m_boardSize);
    std::iota(m_rawBoard.begin(), m_rawBoard.end(), 1);
    shuffle();
}

bool GameBoard::move(const int index)
{
    if(!isPositionValid(static_cast<size_t>(index))) {
        return false;
    }
    const Position elementPosition = getRowCol(index);

    auto hiddenElementIterator = std::find(m_rawBoard.begin(), m_rawBoard.end(), m_boardSize);

    Q_ASSERT(hiddenElementIterator != m_rawBoard.end());

    Position hiddenElementPosition {getRowCol(std::distance(m_rawBoard.begin(), hiddenElementIterator))};

    if(!isAdjacent(elementPosition, hiddenElementPosition)) {
        return false;
    }
    std::swap(*hiddenElementIterator, m_rawBoard.at(index));

    changeStepCount();

    emit dataChanged(createIndex(0, 0), createIndex(m_boardSize, 0));
    return true;
}

bool GameBoard::isWin() const
{
    if(std::is_sorted(m_rawBoard.begin(), m_rawBoard.end()))
        return true;
    else
        return false;
}

void GameBoard::resetTheGame()
{
    m_stepCount = 0;
    shuffle();
    emit stepCountChanged();
    emit dataChanged(createIndex(0, 0), createIndex(m_boardSize, 0));
}

int GameBoard::rowCount(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return m_rawBoard.size();
}

QVariant GameBoard::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || role != Qt::DisplayRole)
        return QVariant{};

    if (!isPositionValid(index.row())) {
           return QVariant{};
       }
    return QVariant((unsigned long long)m_rawBoard.at(index.row()));
}

void GameBoard::shuffle()
{
    static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 generator(seed);

    do {
            std::shuffle(m_rawBoard.begin(), m_rawBoard.end(), generator);
        }
        while (!isBoardValid());

        emit dataChanged(createIndex(0, 0), createIndex(m_boardSize, 0));
}

bool GameBoard::isPositionValid(const size_t position) const
{
    return position < m_boardSize;
}

bool GameBoard::isBoardValid() const
{
    int inv {0};
       for (size_t i {0}; i < m_boardSize; ++i)
           for (size_t j {0}; j < i; ++j)
               if (m_rawBoard[j] > m_rawBoard[i])
                   ++inv;

       const size_t start_point {1};

       for (size_t i {0}; i < m_boardSize; ++i)
           if (m_rawBoard[i] == m_boardSize)
               inv += start_point + i / m_dimension;

       return (inv % 2) == 0;
}

// Conversion 1D (with index) to 2D (row, col)
GameBoard::Position GameBoard::getRowCol(const size_t index) const
{
    Q_ASSERT(index < m_boardSize);
    size_t row = index / m_dimension;
    size_t column = index % m_dimension;

    return std::make_pair(row, column);
}

quint64 GameBoard::getStepCount() const
{
    return m_stepCount;
}

void GameBoard::changeStepCount()
{
    m_stepCount++;
    emit stepCountChanged();
}

size_t GameBoard::getBoardSize() const
{
    return m_boardSize;
}

size_t GameBoard::getDimension() const
{
    return m_dimension;
}
