#ifndef WIN_MNGR_SHOW_INFO_HH
#define WIN_MNGR_SHOW_INFO_HH


#include <list>
#include <string>




namespace win_mngr
{



class ShowInfoWindows;




class I_ShowInfo
{
public:
	I_ShowInfo()                               = default;
	I_ShowInfo(I_ShowInfo const &)             = default;
	I_ShowInfo(I_ShowInfo &&)                  = default;
	I_ShowInfo & operator=(I_ShowInfo const &) = default;
	I_ShowInfo & operator=(I_ShowInfo &&)      = default;

	virtual ~I_ShowInfo();

	I_ShowInfo(std::string const & show_info_name);

	std::string const & show_info_name() const;
	bool show_info_is_open() const;
	void show_info_open() const;

protected:
	//// Called by class ShowInfoWindows
	//
	virtual void _display_show_info_imgui() const = 0;
	//
	/////////////////////////////


private:
	mutable bool m_show_info_is_open = false;
	std::string m_show_info_name;

	friend class ShowInfoWindows;
};








class ShowInfoWindows
{
public:
	ShowInfoWindows();
	~ShowInfoWindows() = default;

	// Will display only one I_ShowInfo Windows if m_display_only_one if true.
	// Will display N I_ShowInfo Windows if m_display_only_one if false.
	static void display_imgui();

private:
	ShowInfoWindows(ShowInfoWindows const &)             = delete;
	ShowInfoWindows(ShowInfoWindows &&)                  = delete;
	ShowInfoWindows & operator=(ShowInfoWindows const &) = delete;
	ShowInfoWindows & operator=(ShowInfoWindows &&)      = delete;

	//// Called by class I_ShowInfo
	//
	void _push_show_info_win(I_ShowInfo const &);
	void _pop_show_info_win(I_ShowInfo const &);
	//
	/////////////////////////////

	void _display_imgui();

	std::list<I_ShowInfo const *> m_show_info_stack;

	friend class I_ShowInfo;
};


extern ShowInfoWindows show_info_windows;







} // win_mngr



#endif // WIN_MNGR_SHOW_INFO_HH