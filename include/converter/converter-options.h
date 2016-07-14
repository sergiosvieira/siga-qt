#ifndef __CONVERTER_OPTIONS__
#define __CONVERTER_OPTIONS__

#include <utility>
#include <tuple>
#include <vector>

using namespace std;
using Range = pair<int, int>; // from, to
using Station = pair<bool, int>; // has station id, id index
using DateIndexes = vector<int>; // date index or day index, month index and year index

enum class Layout
{
    LANDSCAPE,
    PORTRAIT
};

enum class DateFieldCount
{
    SINGLE_FIELD,
    THREE_FIELDS
};

using DateIdentifier = pair<DateFieldCount, DateIndexes>;

/*!
 * \brief The ConverterOptions class
 */
class ConverterOptions
{
public:
    /*!
     * \brief row Range (From, To)
     * \return
     */
    Range rowRange() const;
    /*!
     * \brief set Row Range (From, To)
     * \param rowRange
     */
    void setRowRange(const Range &rowRange);
    /*!
     * \brief col Range (From, To)
     * \return
     */
    Range colRange() const;
    /*!
     * \brief set Col Range (From, To)
     * \param colRange
     */
    void setColRange(const Range &colRange);
    /*!
     * \brief layout (LANDSCAPE, PORTRAIT)
     * \return
     */
    Layout layout() const;
    /*!
     * \brief set Layout (LANDSCAPE, PORTRAIT)
     * \param layout
     */
    void setLayout(const Layout &layout);
    /*!
     * \brief date pair([SINGLE_FIELD or THREE_FIELDS],
     * \return
     */
    DateIdentifier dateIndex() const;
    /*!
     * \brief set single date index
     * \param dateIndex
     */
    void setSingleDate(int dateIndex);
    /*!
     * \brief set trible date indexes
     * \param dayIndex
     * \param monthIndex
     * \param yearIndex
     */
    void setTribleDate(int dayIndex,
                       int monthIndex,
                       int yearIndex);
    /*!
     * \brief date Format
     * \return
     */
    string dateFormat() const;
    /*!
     * \brief set Date Format
     * \param dateFormat
     */
    void setDateFormat(const string &dateFormat);
    /*!
     * \brief there are header field in first line?
     * \return
     */
    bool header() const;
    /*!
     * \brief setHeader
     * \param header
     */
    void setHeader(bool header);
    /*!
     * \brief station
     * \return
     */
    Station station() const;
    /*!
     * \brief setStation
     * \param station
     */
    void setStation(const Station &station);
protected:
    Range m_rowRange = make_pair(1, 1);
    Range m_colRange = make_pair(1, 1);
    Layout m_layout = Layout::LANDSCAPE;
    DateIdentifier m_date;
    string m_dateFormat = "dd/mm/yyyy";
    bool m_header = false;
    Station m_station = make_pair(false, 0);
private:
};

#endif // __CONVERTER_OPTIONS__
