#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QAbstractListModel>
#include <QVector>

class GameBoard : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int dimension READ dimension CONSTANT)
    Q_PROPERTY(int hiddenElementValue READ boardSize CONSTANT)
public:
    using tile_type = size_t;
    using Position = std::pair<size_t, size_t>;
    static constexpr size_t defaultPuzzleDimension {4};
    GameBoard(const size_t boardDimension = defaultPuzzleDimension,
              QObject* parent = nullptr);

    Q_INVOKABLE bool move(int index);
    size_t dimension() const;
    size_t boardSize() const;

    int rowCount(const QModelIndex& index = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;


private:
    void shuffle();
    bool isPositionValid(const size_t position) const;
    bool isBoardValid() const;

    Position getRowCol(size_t index) const;

    std::vector<tile_type> m_rawBoard;
    size_t m_dimension;
    size_t m_boardSize;
};

#endif // GAMEBOARD_H
