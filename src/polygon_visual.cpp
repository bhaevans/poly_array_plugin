#include <OGRE/OgreVector3.h>
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreManualObject.h>

#include "polygon_visual.h"

namespace poly_array_plugin
{
	PolyVisual::PolyVisual( Ogre::SceneManager* scene_manager, Ogre::SceneNode* parent_node )
		: scene_manager_(scene_manager), frame_node_(parent_node->createChildSceneNode()),
			manual_object_(scene_manager_->createManualObject())
	{
		manual_object_->setDynamic(true);
		frame_node_->attachObject(manual_object_);
	}

	PolyVisual::~PolyVisual()
	{
		scene_manager_->destroyManualObject(manual_object_);
		scene_manager_->destroySceneNode(frame_node_);
	}

	void PolyVisual::setMessage(const poly_array_plugin::polygon *msg) const
	{
		Ogre::ColourValue color(msg->color.r,
														msg->color.g,
														msg->color.b,
														msg->color.a);
		uint32_t num_points = msg->polygon.polygon.points.size();
		if (num_points>0)
		{
			manual_object_->estimateVertexCount(num_points);
			manual_object_->begin( "BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP,
															Ogre::ResourceGroupManager::INTERNAL_RESOURCE_GROUP_NAME);
			for (uint32_t i=0; i<num_points+1;++i)
			{
				// Modulo closes polygon, so last point in manual_object_==first point
				const geometry_msgs::Point32& msg_point = msg->polygon.polygon.points[i%num_points];
				manual_object_->position(msg_point.x,msg_point.y,msg_point.z);
				manual_object_->colour(color);
			}
			manual_object_->end();
		}
	}

	void PolyVisual::setFramePosition( const Ogre::Vector3& position)
	{
		frame_node_->setPosition(position);
	}

	void PolyVisual::setFrameOrientation( const Ogre::Quaternion& orientation)
	{
		frame_node_->setOrientation(orientation);
	}

} // ! namespace poly_array_plugin