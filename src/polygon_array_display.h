#ifndef POLYGON_ARRAY_DISPLAY_H
#define POLYGON_ARRAY_DISPLAY_H

#include <vector>

#include <geometry_msgs/PolygonStamped.h>
#include <rviz/message_filter_display.h>

#include "poly_array_plugin/polygon_array.h"

namespace Ogre
{
	class SceneNode;
} // ! namespace Ogre

namespace rviz
{
	class IntProperty;
	class RosTopicProperty;
} // !namespace rviz

namespace poly_array_plugin
{

class PolyVisual;

class PolygonArrayDisplay : public rviz::MessageFilterDisplay<poly_array_plugin::polygon_array>
{
  Q_OBJECT
	public:
		PolygonArrayDisplay();
		virtual ~PolygonArrayDisplay();

	protected:
		virtual void onInitialize();
		virtual void reset();

	//private Q_SLOTS:
	//	void updateQueueSize();
	//	void updateTopic();

	private:
		void processMessage(
			const poly_array_plugin::polygon_array::ConstPtr& msg
		) override;
		std::vector<PolyVisual> visuals_;

		//rviz::IntProperty* queue_size_property_;
		//rviz::RosTopicProperty* topic_property_;
};
    
} // ! namespace poly_array_plugin


#endif // !POLYGON_ARRAY_DISPLAY_H