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
using TreeNodeType = tree<TreeNode>;
using TreeNodeIterator = TreeNodeType::iterator;

namespace SIGA
{
    namespace DS
    {
        /** Predefined values **/
        enum class PeriodType
        {
            NONE = 0x0000,
            HOURLY_TYPE  = 0x1111,
            DAILY_TYPE  = 0x0111,
            MONTHLY_TYPE  = 0x0011,
            YEARLY_TYPE  = 0x0001
        }; // NONE = 0x0000, HOURLY_TYPE  = 0x1111, DAILY_TYPE  = 0x0111, MONTHLY_TYPE  = 0x0011, YEARLY_TYPE  = 0x0001
        using DayMonthYearNodes = std::tuple<TreeNode*, TreeNode*, TreeNode*>;
        using DateIDValueParameters = std::tuple<CDate, int, float>;
        using DayMonthYearValue = std::tuple<float, float, float>;
        /*!
         * \brief The TimeSerieTree class
         * Used to store a time serie in a Tree Data Structure
         */
        class TimeSerieTree
        {
        private:
            using VectorOfInt = vector<int>;
            using VectorOfString = vector<string>;
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
            /*!
             * \brief set station date value
             * \param a_date
             * \param id
             * \param a_value
             * \return Success(true) - Fail(false)
             */
            bool setDateValue(const CDate& a_date,
                              const int& id,
                              const float& a_value);
            /*! To do: is it really needed? */
            void clearStations();
            /*!
             * \brief returns each date (day, month and year) value from station
             * \param date
             * \param id
             * \return
             */
            DayMonthYearValue dateValues(const CDate& date,
                                         const int& id);
            /*!
             * \brief get daily value in date from id
             * \param date
             * \param id
             * \return
             */
            float dayValue(const CDate& date,
                           const int& id);
            /*!
             * \brief get monthly value in date from id
             * \param date
             * \param id
             * \return
             */
            float monthValue(const CDate& date,
                             const int& id);
            /*!
             * \brief get yearly value in date from id
             * \param date
             * \param id
             * \return
             */
            float yearValue(const CDate& date,
                            const int& id);
            /*!
             * \brief sort values
             */
            void sortValues();
            /*!
             * \brief depth of tree
             * \param a_nodeIterator
             * \return
             */
            int depth(TreeNodeIterator& a_nodeIterator) const;
            /*!
             * \brief stations Length
             * \return
             */
            int stationsLength() const;
            /*!
             * \brief rows Length
             * \return
             */
            int rowsLength() const;
            /*!
             * \brief id's labels
             * \return
             */
            VectorOfString stationLabels() const;
            /*!
             * \brief station ID from its index
             * \param a_index
             * \return
             */
            int stationID(int a_index) const;
            /*!
             * \brief begin tree iterator
             * \return
             */
            inline TreeNodeIterator begin() const
            {
                return m_tree.begin();
            }
            /*!
             * \brief end tree iterator
             * \return
             */
            inline TreeNodeIterator end() const
            {
                return m_tree.end();
            }
            /*!
             * \brief years
             * \return
             */
            int numberOfYears() const;
            /*!
             * \brief tree period type
             * \return
             */
            PeriodType periodType() const;
            /*!
             * \brief tree size
             * \return
             */
            int size() const;
        protected:
            VectorOfInt m_stations;
            tree<TreeNode> m_tree;
            int m_rows = 0;
            int m_yearsCounter = 0;
            PeriodType m_type;
        private:
            /*!
             * \brief get pointers to day, month and year TreeNode
             * \param a_date
             * \return
             */
            DayMonthYearNodes nodesFromDate(const CDate& a_date);
            /*!
             * \brief insert value on year node, all month nodes and all day nodes
             *   Year - insert value
             *   For each month
             *     insert value / 12
             *   For each day
             *     insert value / 365 or value / 366
             * \param nodes
             * \param parameters
             * \return
             */
            bool insertYearlyValue(DayMonthYearNodes& nodes,
                                   DateIDValueParameters& parameters);
            /*!
             * \brief insert value on year node, month node and all day nodes
             *   Year - sum value to current year node value
             *   Month - insert value
             *   For each day
             *     insert value / 31 or value / 30 or value / 29 or value / 28
             * \param nodes
             * \param parameters
             * \return
             */
            bool insertMonthlyValue(DayMonthYearNodes& nodes,
                                    DateIDValueParameters& parameters);
            /*!
             * \brief insert value on year node, month node and day node
             *   Year - sum value to current yearly node value
             *   Month - sum value to current monthly node value
             *   Day - insert value
             * \param nodes
             * \param parameters
             * \return
             */
            bool insertDailyValue(DayMonthYearNodes& nodes,
                                  DateIDValueParameters& parameters);
            /*!
             * \brief get station index from station id
             * \param id
             * \return
             */
            int stationIndex(int id);
            /*!
             * \brief fill all node's children values
             * \param base
             * \param value
             */
            void insertID(const int& id);
        };

    }
}

#endif /** __TIME_SERIE_TREE__ **/
