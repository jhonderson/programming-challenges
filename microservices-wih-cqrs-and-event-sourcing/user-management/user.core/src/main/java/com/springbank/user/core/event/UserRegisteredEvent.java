package com.springbank.user.core.event;

import com.springbank.user.core.domain.User;
import lombok.Builder;
import lombok.Data;

@Data
@Builder
public class UserRegisteredEvent {
    private String id;
    private User user;
}
