#pragma once
#include "MTSView.h"
class MTSTableView :
    public MTSView
{
public:
    using MTSView::MTSView;
    void render() override;
    void addCell(std::shared_ptr<MTSView> cell);
    void setRowHeight(int height);


    std::shared_ptr<MTSView> getCell(unsigned index) const;

    std::size_t getCellNum() const;

    int m_rowHeight{ 80 };
private:
    std::vector<std::weak_ptr<MTSView>> m_cells{};
};

