package com.springbank.user.query.api.handler;

import com.springbank.user.core.domain.User;
import lombok.AllArgsConstructor;
import lombok.Data;

import java.util.Collections;
import java.util.List;

@Data
@AllArgsConstructor
public class UserQueryResult {
    private List<User> users;

    public UserQueryResult(final User user) {
        this(Collections.singletonList(user));
    }
}
