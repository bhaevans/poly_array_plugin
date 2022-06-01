#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSceneManager.h>

#include <tf/transform_listener.h>

#include <rviz/visualization_manager.h>
#include <rviz/frame_manager.h>
//#include <rviz/properties/ros_topic_property.h">
#include <rviz/properties/int_property.h>

#include "polygon_visual.h"
#include "polygon_array_display.h"

namespace poly_array_plugin
{
	PolygonArrayDisplay::PolygonArrayDisplay() {}

	PolygonArrayDisplay::~PolygonArrayDisplay() {}

	void PolygonArrayDisplay::onInitialize()
	{
		MFDClass::onInitialize();
	}

	void PolygonArrayDisplay::reset()
	{
		MFDClass::reset();
		visuals_.clear();
	}

	void PolygonArrayDisplay::processMessage(const poly_array_plugin::polygon_array::ConstPtr& msg)
	{
		Ogre::Quaternion orientation;
		Ogre::Vector3 position;
		if (!context_->getFrameManager()->getTransform( msg->header.frame_id,
																										msg->header.stamp,
																										position, orientation))
		{
			ROS_DEBUG( "Error transforming from frame '%s' to frame '%s'",
									msg->header.frame_id.c_str(), qPrintable( fixed_frame_));
			return;
		}	

		for (auto polygon_msg : msg->polygons)
		{
			visuals_.emplace_back(context_->getSceneManager(), scene_node_);
			PolyVisual& visual = visuals_.back();
			visual.setMessage(&polygon_msg);
			visual.setFramePosition(position);
			visual.setFrameOrientation(orientation);
		}
	}

	//void PolygonArrayDisplay::updateQueueSize()
	//{
	//
	//}

} // namespace poly_array_plugin

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(poly_array_plugin::PolygonArrayDisplay, rviz::Display)