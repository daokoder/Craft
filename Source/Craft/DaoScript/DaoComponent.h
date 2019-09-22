//
// Copyright (c) 2019 the Craft Engine project.
// Copyright (c) 2016, Limin Fu
// 
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//

#ifndef __DAO_COMPONENT_H__
#define __DAO_COMPONENT_H__

#include "../Script/ScriptComponent.h"

#include "DaoComponentFile.h"

namespace Craft
{

class DaoVM;

/// Dao script component
class CRAFT_API DaoComponent : public ScriptComponent
{
    friend class DaoComponentFactory;
    friend class DaoComponentFile;

    CRAFT_OBJECT(DaoComponent,ScriptComponent);

    enum EventFlags
    {
        USE_UPDATE = 0x1,
        USE_POSTUPDATE = 0x2,
        USE_FIXEDUPDATE = 0x4,
        USE_FIXEDPOSTUPDATE = 0x8
    };

public:

    /// Construct.
    DaoComponent(Context* context);
    /// Destruct.
    virtual ~DaoComponent();

    /// Register object factory.
    static void RegisterObject(Context* context);

    bool Load(Deserializer& source);
    bool LoadXML(const XMLElement& source);
    void ApplyAttributes();

    /// Match script name
    bool MatchScriptName(const String& path);

    /// Handle enabled/disabled state change. Changes update event subscription.
    virtual void OnSetEnabled();

    /// Set what update events should be subscribed to. Use this for optimization: by default all are in use. Note that this is not an attribute and is not saved or network-serialized, therefore it should always be called eg. in the subclass constructor.
    void SetUpdateEventMask(unsigned char mask);

    /// Return what update events are subscribed to.
    unsigned char GetUpdateEventMask() const { return updateEventMask_; }
    /// Return whether the DelayedStart() function has been called.
    bool IsDelayedStartCalled() const { return delayedStartCalled_; }

    void SetDestroyed() { destroyed_ = true; }

    /// Get script attribute
    ResourceRef GetComponentFileAttr() const;
    ScriptComponentFile* GetComponentFile() const { return componentFile_; }

    /// Set script attribute.
    void SetComponentFile(DaoComponentFile* cfile) { componentFile_ = cfile; }
    void SetComponentFileAttr(const ResourceRef& value);

    // a DaoComponentFile only holds one class, so no classname to look up in it
    const String& GetComponentClassName() const { return String::EMPTY; }

	void SetObject( DaoObject *object );

	void SetData( const char *key, DaoValue *data );
	DaoValue* GetData( const char *key );


protected:
    /// Handle scene node being assigned at creation.
    virtual void OnNodeSet(Node* node);
    /// Handle scene being assigned.
    virtual void OnSceneSet(Scene* scene);

    /// Called when the component is added to a scene node. Other components may not yet exist.
    virtual void Start() { }
    /// Called before the first update. At this point all other components of the node should exist. Will also be called if update events are not wanted; in that case the event is immediately unsubscribed afterward.
    virtual void DelayedStart() { }
    /// Called when the component is detached from a scene node, usually on destruction. Note that you will no longer have access to the node and scene at that point.
    virtual void Stop() { }
    /// Called on scene update, variable timestep.
    virtual void Update(float timeStep) { }
    /// Called on scene post-update, variable timestep.
    virtual void PostUpdate(float timeStep) { }
    /// Called on physics update, fixed timestep.
    virtual void FixedUpdate(float timeStep) { }
    /// Called on physics post-update, fixed timestep.
    virtual void FixedPostUpdate(float timeStep) { }

private:
    /// Subscribe/unsubscribe to update events based on current enabled state and update event mask.
    void UpdateEventSubscription();
    /// Handle scene update event.
    void HandleSceneUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle scene post-update event.
    void HandleScenePostUpdate(StringHash eventType, VariantMap& eventData);
#ifdef CRAFT_PHYSICS
    /// Handle physics pre-step event.
    void HandlePhysicsPreStep(StringHash eventType, VariantMap& eventData);
    /// Handle physics post-step event.
    void HandlePhysicsPostStep(StringHash eventType, VariantMap& eventData);
#endif


    /// Requested event subscription mask.
    unsigned char updateEventMask_;
    /// Current event subscription mask.
    unsigned char currentEventMask_;

    bool instanceInitialized_;
    bool started_;
    bool destroyed_;
    bool scriptClassInstance_;

    /// Flag for delayed start.
    bool delayedStartCalled_;

    bool loading_;
    SharedPtr<DaoComponentFile> componentFile_;

	DaoObject  *object;
	DString    *key;
	DMap       *aux;

};

}

#endif
