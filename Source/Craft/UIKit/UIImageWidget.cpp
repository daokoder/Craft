//
// Copyright (c) 2014-2015, THUNDERBEAST GAMES LLC All rights reserved
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include <TurboBadger/tb_widgets.h>
#include <TurboBadger/tb_widgets_common.h>
#include <TurboBadger/image/tb_image_widget.h>

#include "../IO/Log.h"

#include "UI.h"
#include "UIEvents.h"
#include "UIWidget.h"
#include "UIImageWidget.h"

using namespace tb;

namespace Craft {

namespace UIKit
{

UIImageWidget::UIImageWidget(Context* context, bool createWidget) : UIWidget(context, false)
{
    if (createWidget)
    {
        widget_ = new TBImageWidget();
        widget_->SetDelegate(this);
        GetSubsystem<UI>()->WrapWidget(this, widget_);
    }
}

UIImageWidget::~UIImageWidget()
{
}

int UIImageWidget::GetImageWidth() const
{
    if (!widget_)
        return 0;

    return ((TBImageWidget*) widget_)->GetImageWidth();

}

int UIImageWidget::GetImageHeight() const
{
    if (!widget_)
        return 0;

    return ((TBImageWidget*) widget_)->GetImageHeight();

}

void UIImageWidget::SetImage(const String& imagePath)
{
    if (!widget_)
        return;

    ((TBImageWidget*) widget_)->SetImage(imagePath.CString());

}

bool UIImageWidget::OnEvent(const tb::TBWidgetEvent &ev)
{
    return UIWidget::OnEvent(ev);
}

}}
