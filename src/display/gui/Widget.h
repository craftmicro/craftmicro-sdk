#pragma once

#include "display/DisplayObject.h"
#include "display/Sprite.h"
#include "display/Text.h"
#include "display/gui/Style.h"

namespace craft {

    /**
     * @brief Register of widget types
     */
    typedef enum {
        WTMin = 1,
        WTWindow = 1,
        WTMenu = 2,
        WTMax = 2
    } WidgetType;

    /**
     * The GUI widget base class
     * Provides functionallity common to all GUI widgets.
     */
    class Widget : public DisplayObject {
    public:
        /**
         * @brief Construct a new Widget object
         */
        Widget();

        /**
         * @brief Construct a new Widget object
         *
         * @param style The style to set
         */
        Widget(Style* style);

        /**
         * @brief Set the Style object
         * Usually the style is inherited from the parent, but calling this method allows the widget
         * to use a completely different style if required. Add new child GUI objects will inherit
         * this new style. Any existing child GUI objects will only inherit the style if the
         * setForChildren flag is true.
         * @param style The style to set
         * @param setForChildren If true, will also set the style (recursively) for all children
         */
        virtual void style(Style* style, bool setForChildren = true);

        /**
         * @brief Get the style object
         * @return Style* The style object
         */
        virtual Style* style();

        /**
         * @brief Change the title and acronym of the widget
         *
         * @param title The title (copied)
         * @param acronym A short acronym when the full title cannot be displayed. Max 4 characters. (copied)
         */
        virtual void title(char* title = nullptr, char* acronym = nullptr);

        /**
         * @brief Change the icon
         * @see style->icons
         * @param index The index of the icon
         */
        int icon = -1;

        /**
         * @brief Reset the widget back to defaults
         */
        virtual void reset() override;

        /**
         * @brief Set the window width
         *
         * @param w The window width
         */
        void width(float_t w) override;

        /**
         * @brief Return the window width
         *
         * @return float_t The window width
         */
        float_t width() override { return DisplayObject::width(); }

        /**
         * @brief Set the window height
         *
         * @param h The window height
         */
        void height(float_t h) override;

        /**
         * @brief Return the window height
         *
         * @return float_t The window height
         */
        float_t height() override { return DisplayObject::height(); }

        /**
         * @brief Arrange children to fit thie object
         * Called automatically when size changes ot when children are
         * added or removed. May need to be called manually in certain
         * occasions.
         */
        virtual void arrange();

        /**
         * @brief Begin the render sweep for the current frame
         * @param updateArea The area of the display being updated
         */
        virtual void beginRender(ClipRect* updateArea) override;

    protected:

        /**
         * @brief The style object
         */
        Style* _style = nullptr;

        /**
         * @brief The widget title
         */
        char* _title = nullptr;

        /**
         * @brief The widget acronym
         */
        char* _acronym = nullptr;

        /**
         * @brief Flag to indicate that an arrange is required
         */
        bool _needsArrange = true;

        /**
         * @brief Called when a display object is added to this object
         * Ensure child GUI widgets are processed correctly
         * @param child The object being added
         */
        virtual void _added(DisplayObject* child) override;

        /**
         * @brief Called when a display object is removed from this object
         * Ensure child GUI widgets are processed correctly
         * @param child The object being removed
         */
        virtual void _removed(DisplayObject* child) override;

        /**
         * @brief Text area for the title
         */
        Text* _label;

        /**
         * @brief Sprite for the icon
         */
        Sprite* _icon;

    };

} // namespace craft
