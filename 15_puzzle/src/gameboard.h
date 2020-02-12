#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QAbstractListModel>
#include <QVector>
#include <QTime>

class GameBoard : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int dimension READ getDimension CONSTANT)
    Q_PROPERTY(int hiddenElementValue READ getBoardSize CONSTANT)
    Q_PROPERTY(quint64 stepCount READ getStepCount NOTIFY stepCountChanged)
public:
    using tile_type = size_t;
    using Position = std::pair<size_t, size_t>;
    static constexpr size_t defaultPuzzleDimension {4};
    GameBoard(const size_t boardDimension = defaultPuzzleDimension,
              QObject* parent = nullptr);

    Q_INVOKABLE bool move(const int index);
    Q_INVOKABLE bool isWin() const;
    Q_INVOKABLE void resetTheGame();

    size_t getDimension() const;
    size_t getBoardSize() const;
    quint64 getStepCount() const;


    int rowCount(const QModelIndex& index = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;



signals:
    void stepCountChanged();

private:
    void shuffle();
    bool isPositionValid(const size_t position) const;
    bool isBoardValid() const;
    void changeStepCount();

    Position getRowCol(size_t index) const;

    std::vector<tile_type> m_rawBoard;
    size_t m_dimension;
    size_t m_boardSize;
    quint64 m_stepCount;
};

#endif // GAMEBOARD_H
