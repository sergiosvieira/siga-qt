/****************************************************************************
 Copyright (c) 2016 Funceme
 Author: Sérgio Vieira - sergiosvieira@gmail.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __TIME_SERIE_TREE__
#define __TIME_SERIE_TREE__


#include "tree.h"
#include "tree-node.h"
#include "sparse-matrix.h"
#include "../date/cdate.h"

/** C++ **/
#include <functional>

using namespace std;
using namespace SIGA::DS;
using TreeNodeIterator = tree<TreeNode>::iterator;

namespace SIGA
{
    namespace DS
    {
        /** Predefined value **/
        enum class PeriodType
        {
            NONE = 0x0000,
            HOURLY_TYPE  = 0x1111,
            DAILY_TYPE  = 0x0111,
            MONTHLY_TYPE  = 0x0011,
            YEARLY_TYPE  = 0x0001
        }; // NONE = 0x0000, HOURLY_TYPE  = 0x1111, DAILY_TYPE  = 0x0111, MONTHLY_TYPE  = 0x0011, YEARLY_TYPE  = 0x0001
        /*!
         * \brief The TimeSerieTree class
         * Used to store a time serie in a Tree Data Structure
         */
        class TimeSerieTree
        {
        public:
            /*!
             * \brief Default Constructor
             */
            TimeSerieTree();
            /*!
             * \brief Overloaded Constructor
             * \param year
             * \param type
             */
            TimeSerieTree(int year,
                          PeriodType type);
            /*!
             * Default destructor
             */
            ~TimeSerieTree();
            /*!
             * \brief createTreeNodes
             * \param year
             * \param type
             */
            void createTreeNodes(int year,
                                 PeriodType type);
            /**
                @return value inserted with success - true or false
            **/
            bool insertValueOnStation(const CDate& a_date,
                                      const int& a_stationID,
                                      const float& a_value);
            void insertStationID(const int& a_stationID);
            void clearStations();
            /**
                @return day value, month (sum of days), year (sum of months)
            **/
            std::tuple<float, float, float> valueOnStation(const CDate& date,
                                                           const int& stationID);
            void sortValues();
            int depth(TreeNodeIterator& a_nodeIterator) const;
            int stationsLength() const;
            int rowsLength() const;
            std::vector<std::string> stationLabels() const;
            int stationID(int a_index) const;
            inline TreeNodeIterator begin() const
            {
                return m_tree.begin();
            }
            inline TreeNodeIterator end() const
            {
                return m_tree.end();
            }
            int yearsLenght() const;
            PeriodType periodType() const;
            int size() const;
        protected:
            std::vector<int> m_stations;
            tree<TreeNode> m_tree;
            int m_rows = 0;
            int m_yearsCounter = 0;
            PeriodType m_type;
        private:
            typedef std::function<void(TreeNodeIterator&)> HourFunction;
            typedef std::function<void(TreeNodeIterator&, int, HourFunction)> DayFunction;
            void appendMonths(int a_year,
                              TreeNodeIterator& a_yearIt,
                              DayFunction a_dayFunction = nullptr,
                              HourFunction a_hourFunction = nullptr);
            void appendDays(TreeNodeIterator& a_monthIt,
                            int a_daysInMonth,
                            HourFunction a_hourFunction = nullptr);
            void appendHours(TreeNodeIterator& a_dayIt);
            void destroyValues();
            void updateNodeValue(TreeNode* node,
                                 const float& value,
                                 const int& stationIndex);
            /**
                @return day, month, year
            **/
            std::tuple<TreeNode*, TreeNode*, TreeNode*> nodesFromDate(const CDate& a_date);
        };

    }
}

#endif /** __TIME_SERIE_TREE__ **/
