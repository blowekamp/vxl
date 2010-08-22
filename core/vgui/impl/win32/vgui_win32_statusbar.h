// This is core/vgui/impl/win32/vgui_win32_statusbar.h
#ifndef vgui_win32_statusbar_h_
#define vgui_win32_statusbar_h_
//:
// \file
// \brief The Win32 Application Programming Interfaces (API) implementation of vgui_statusbar.
// \author Lianqing Yu
// \date   August 4, 2009
//
// Modifications:
//  August 4, 2009              Initial version

#include <vcl_string.h>
#include <vcl_iosfwd.h> // for the declaration of vcl_ostream

#include <vgui/vgui_statusbar.h>
#include <vgui/vgui_statusbuf.h>

#include <windows.h>

#define NUMSECTION 255 // A status bar can have a maximum of 255 sections.

class vgui_win32_statusbar : public vgui_statusbar
{
 public:
  vgui_win32_statusbar(HWND hwndParent, int numPanes = 1);
  ~vgui_win32_statusbar();

  //: show or hide status bar.
  void setVisible(bool visible) { ShowWindow(_hwnd, visible?SW_SHOW:SW_HIDE); }

  //: Get window handle of status bar
  HWND getWindowHandle() { return _hwnd; }

  //: Append given text (of given length) to the status bar
  virtual int write(const char* text, int n);
  //: Append given text to the status bar
  virtual int write(const char* text);

  vcl_string linebuffer;
  vgui_statusbuf *statusbuf;
  vcl_ostream out;

 private:
  static int statusBarID;

  HWND _hwndParent; //!< parent (main) window of the status bar.
  HWND _hwnd;
  int _numPanes; //!< number of panes (parts)
};

#endif // vgui_win32_statusbar_h_
