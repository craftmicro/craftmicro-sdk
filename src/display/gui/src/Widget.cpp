#include "../Widget.h"

namespace craft {

    Widget::Widget() {}

    Widget::Widget(Style* style) {
        this->_style = style;
        /*
        this->_icon = Sprite::Create( _style->icons, 0 );
        addChild( this->_icon );
        this->_label = Text::Create( _style->labelFont );
        addChild( this->_label );
        */
    }

    void Widget::reset() {
        DisplayObject::reset();
        if (_title) delete _title;
        if (_acronym) delete _acronym;
        icon = 0;
    }

    void Widget::title(char* title, char* acronym) {
        if (this->_title) {
            delete this->_title;
            this->_title = nullptr;
        }
        if (this->_acronym) {
            delete this->_acronym;
            this->_acronym = nullptr;
        }
        if (title) {
            int len = craft::min(CRAFTMICRO_GUI_MAX_TITLE_LEN, strlen((const char*)title));
            this->_title = new char[len + 1];
            strncpy(this->_title, (const char*)title, len);
        }
        if (acronym) {
            this->_acronym = new char[CRAFTMICRO_GUI_MAX_ACRONYM_LEN + 1];
            strncpy(this->_acronym, (const char*)acronym, CRAFTMICRO_GUI_MAX_ACRONYM_LEN);
        }
        else if (title) {
            // Create an acronym from the title. CamelCase, ignores whitespace. Examples:
            // My Widget` = MyW, Settings = Set, M8tes = M8t etc
            this->_acronym = new char[CRAFTMICRO_GUI_MAX_ACRONYM_LEN + 1];
            int count = CRAFTMICRO_GUI_MAX_ACRONYM_LEN;
            int soffset = 0;
            int doffset = 0;
            bool caps = true;
            while (doffset < count) {
                char p = title[soffset];
                if (p == '\0') {
                    this->_acronym[doffset] = '\0';
                    break;
                }
                else if (isalpha(p) || isdigit(p)) {
                    if (caps) this->_acronym[doffset] = toupper(p);
                    else this->_acronym[doffset] = p;
                    caps = false;
                    doffset++;
                }
                else {
                    caps = true;
                }
                soffset++;
            }
        }
        this->_title = title;
        if (acronym) this->_acronym = acronym;
        else this->_acronym = this->_title;
    }

    void Widget::_added(DisplayObject* child) {
        // if the child is a GUI Display Object
        if (child->type >= WidgetType::WTMin && child->type <= WidgetType::WTMax) {
            ((Widget*)child)->style(_style, true);
        }
        _needsArrange = true;
    }

    void Widget::_removed(DisplayObject* child) {
        _needsArrange = true;
    }

    void Widget::style(Style* style, bool setForChildren) {
        this->_style = style;
        if (setForChildren) {
            DisplayObject* child = _children;
            while (child) {
                if (child->type >= WidgetType::WTMin && child->type <= WidgetType::WTMax) {
                    ((Widget*)child)->style(style);
                    child->dirty();
                }
                child = child->next();
            }
        }
        dirty();
    }

    Style* Widget::style() {
        return _style;
    }

    void Widget::width(float_t w) {
        DisplayObject::width(w);
        _needsArrange = true;
    }

    void Widget::height(float_t h) {
        DisplayObject::height(h);
        _needsArrange = true;
    }

    void Widget::beginRender(ClipRect* updateArea) {
        if (_needsArrange) arrange();
        DisplayObject::beginRender(updateArea);
    }

    void Widget::arrange() {
        /*
        if ( icon >= 0 ) {
            _icon->visible( true );
            _icon->set( _style->icons, icon );
        }
        else {
            _icon->visible( false );
        }
        if ( _title ) {
            _label->visible( true );
            _label->text( _title );
        }
        else {
            _label->visible( false );
        }
        */
        DisplayObject* child = _children;
        while (child) {
            if (child->type >= WidgetType::WTMin && child->type <= WidgetType::WTMax) {
                ((Widget*)child)->arrange();
            }
            child = child->next();
        }
        _needsArrange = false;
    }

} // namespace craft
