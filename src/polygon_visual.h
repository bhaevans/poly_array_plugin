#ifndef POLYGON_VISUAL_H
#define POLYGON_VISUAL_H

#include "poly_array_plugin/polygon.h"

namespace Ogre
{
  class ManualObject;
	class SceneNode;
	class SceneManager;
} // !namespace Ogre

namespace poly_array_plugin
{
	class PolyVisual
	{
		public:
			PolyVisual( Ogre::SceneManager* scene_manager, Ogre::SceneNode* parent_node );

			virtual ~PolyVisual();

			void setMessage(const poly_array_plugin::polygon *msg) const;

			void setFramePosition( const Ogre::Vector3& position );
			void setFrameOrientation( const Ogre::Quaternion& orientation);

		private:
			Ogre::SceneManager* scene_manager_;
			Ogre::SceneNode* frame_node_;
			Ogre::ManualObject* manual_object_;
			
			
	};
} // !namespace poly_array_plugin


#endif //! POLYGON_ARRAY_VISUAL_H