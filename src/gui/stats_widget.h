#pragma once

#include <QDialog>
#include <vector>
#include <map>
#include "../trenchcoat.h"

class StatsWidget : public QDialog {
    Q_OBJECT

    private:
        const std::vector<Trenchcoat> data;

        std::map<std::string, unsigned int> getStocks(const std::string& color) const;

    public:
        StatsWidget(const std::vector<Trenchcoat>& data, 
                    QWidget *parent);
};
