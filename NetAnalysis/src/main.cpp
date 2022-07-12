#include "main.hpp"
#include <fstream>
#include <iostream>
#include <iterator>
#include <json/json.h>
#include <json/json_features.h>
#include <json/value.h>
#include <qfiledialog.h>
#include <string>
#include <vector>

int main(int argc, char **argv)
{
    QApplication *app = new QApplication(argc, argv);
    auto fileName = QFileDialog::getOpenFileName();
    auto analyzer = new NetAnalysis::GraphMeasures::GraphAnalyzer();
    analyzer->LoadGraph(fileName.toStdString());
    // auto features = QFileDialog::getOpenFileName();
    // analyzer->PopulateFeatures(features.toStdString());
    NetAnalysis::Routines::ExecuteCommunityAnalysis(analyzer);
    NetAnalysis::Routines::AnalyzeCentrality(analyzer);
    NetAnalysis::Routines::AveragePathLength(analyzer);
    NetAnalysis::Routines::ClusteringCoefficients(analyzer);
    NetAnalysis::Routines::DegreeAverage(analyzer);
    NetAnalysis::Routines::ExecuteComponentsAnalysis(analyzer);

    return app->exec();
}