package com.springbank.user.core.domain;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

import javax.validation.constraints.Email;
import javax.validation.constraints.NotEmpty;
import javax.validation.constraints.NotNull;

@Data
@AllArgsConstructor
@NoArgsConstructor
@Builder
@Document(collection = "users")
public class User {
    // This validation and spring-data annotations should not be in the domain
    // The validation annotations should be in the request/command objects
    // The sprint-data annotations should be in a mongodb adapter
    // I am too lazy for that now, just wanted to practice using event sourcing and CQRS with spring
    @Id
    private String id;
    @NotEmpty
    private String firstName;
    @NotEmpty
    private String lastName;
    @Email(message = "invalid email address")
    private String emailAddress;
    @NotNull
    private Account account;
}
