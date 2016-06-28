//
// Created by sooda on 16/6/27.
//

#include "modules/LabelGenerator.h"
#include "common.h"

namespace cppmary {
    LabelGenerator::LabelGenerator(FeatureProcessorManager* manager, TargetFeatureComputer* featureComputer, const std::string& featureMapName) {
        manager_ = manager;
        featureComputer_ = featureComputer;
        loadDict(featureName_, featureAlias_, featureMapName);
        assert(featureName_.size() == featureAlias_.size());
//        for (int i = 0; i < featureName_.size(); i++) {
//            std::cout << featureName_[i] << " " << featureAlias_[i] << std::endl;
//        }
    }
    LabelGenerator::~LabelGenerator() {}

    std::string LabelGenerator::process(std::string input) {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_string(input.c_str());
        phone_boundary_walker tw;
        doc.traverse(tw);
        std::vector<Target> targets = createTargetWithPauses(tw.nodes_, "_");
        std::string label = "";
        for (int i = 0; i < targets.size(); i++) {
            Target target = targets[i];
            std::map<std::string, std::pair<int, std::string> > detail;
            std::vector<int> features = featureComputer_->computeFeatureVector(target, &detail);
//            std::cout << target.getName() << "\t" ;
//            std::map<std::string, std::pair<int, std::string> >::iterator iter;
//            for (iter = detail.begin(); iter != detail.end(); iter++) {
//                std::cout << iter->first << " " << iter->second.first << " " << iter->second.second << std::endl;
//            }
//            std::cout << std::endl << std::endl;
            //construct label string
            //need to repalce trickyphone, repalce punc, replace tobi
            label = label + detail["prev_prev_phone"].second + "^" + detail["prev_phone"].second + "-" + detail["phone"].second + "+" + detail["next_phone"].second + "=" + detail["next_next_phone"].second + "|";
            for (int i = 0; i < featureName_.size(); i++) {
                std::string featureName = featureName_[i];
                std::string featureAlias = featureAlias_[i];
                std::string featureValue = detail[featureName].second;
                if (featureValue.empty()) {
                    featureValue = "0";
                }
                label = label + "|" + featureAlias + "=" + featureValue;
            }
            label = label + "||\n";
        }
        std::cout << label << std::endl;
        return input;
    }


    std::vector<Target> LabelGenerator::createTargetWithPauses(std::vector<pugi::xml_node> segmentsAndPauses,
                                               std::string pauseSymbol) {
        std::vector<Target> targets;
        if (segmentsAndPauses.size() == 0) {
            return targets;
        }
        //TODO: add final boundary
        for (int i = 0; i < segmentsAndPauses.size(); i++) {
            pugi::xml_node seg = segmentsAndPauses[i];
            std::string phone = seg.attribute("p").as_string();
            if (phone == "") {
                phone = pauseSymbol;
            }
            Target temp(phone, seg);
            targets.push_back(temp);
        }
        return targets;
    }
}