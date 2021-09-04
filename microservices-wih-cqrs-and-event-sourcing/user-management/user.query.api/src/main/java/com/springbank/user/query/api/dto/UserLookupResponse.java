package com.springbank.user.query.api.dto;

import com.springbank.user.core.domain.User;
import com.springbank.user.core.dto.BaseResponse;
import lombok.Getter;

import java.util.List;

@Getter
public class UserLookupResponse extends BaseResponse {
    private List<User> users;

    public UserLookupResponse(final String message) {
        super(message);
    }

    public UserLookupResponse(final List<User> users) {
        this((String) null);
        this.users = users;
    }
}
