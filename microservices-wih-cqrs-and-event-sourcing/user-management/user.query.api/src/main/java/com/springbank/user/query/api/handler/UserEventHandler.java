package com.springbank.user.query.api.handler;

import com.springbank.user.core.event.UserRegisteredEvent;
import com.springbank.user.core.event.UserRemovedEvent;
import com.springbank.user.core.event.UserUpdatedEvent;

public interface UserEventHandler {
    void on(UserRegisteredEvent event);
    void on(UserUpdatedEvent event);
    void on(UserRemovedEvent event);
}
